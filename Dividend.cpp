#include "Dividend.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;

Dividend::Dividend(string start_date_, float initial_capital, string pay_freq_, string stock_info, bool status):Investment(initial_capital, stock_info){

     // Debugging output for constructor parameters
    std::cout << "Initializing Dividend: Start Date = " << start_date_ 
              << ", Initial Capital = " << initial_capital 
              << ", Pay Frequency = " << pay_freq_ 
              << ", Stock Info = " << stock_info 
              << ", Reinvest Status = " << std::boolalpha << status << std::endl;

    set_reinvest_status(status);

    set_investment_type();

    set_final_capital(0);

    if (valid_pay_freq(pay_freq_)){
        if (valid_start_date(start_date_)){
                       std::cerr << "valid start date is checked" << std::endl;
            if (get_close_prices().empty() || get_dates().empty()) {
                            std::cerr << "Error: Essential data (close prices or dates) is missing." << std::endl;
                            return;  // Exit if data is missing
                        }

                        // Run investment strategy
                        investment_stratergy();
                    } else {
                        std::cerr << "Error: Invalid start date provided." << std::endl;
                    }
                } else {
                    std::cerr << "Error: Invalid pay frequency provided." << std::endl;
                }
            }
    

void Dividend::investment_stratergy() {
    // Validate essential data
    if (get_close_prices().empty() || get_dates().empty()) {
        std::cerr << "Error: Missing close prices or dates data in investment strategy." << std::endl;
        return;
    }

    // Check if the index is within bounds
    if (get_index() >= get_close_prices().size()) {
        std::cerr << "Error: Invalid index for accessing close prices." << std::endl;
        return;
    }

    // Calculate initial number of shares
    float num_shares = get_capital() / get_close_prices()[get_index()];
    std::cout << "Initial number of shares: " << num_shares << std::endl;

    float payment = 0;
    int frequencey_pay = 0;
    float division_factor = 1.0;

    // Determine frequency and division factor based on pay frequency
    if (get_pay_freq() == "Monthly") {
        frequencey_pay = 30;
        division_factor = 12;
    } else if (get_pay_freq() == "Quarterly") {
        frequencey_pay = 92;
        division_factor = 4;
    }

    // No reinvestment strategy
    if (!reinvest_status) {
        payment = get_capital();
        for (int i = get_index(); i < get_dates().size(); i++) {
            float dividend = (get_close_prices()[i] * (0.03) / 365) * num_shares;
            payment += dividend;
        }
        set_final_capital(payment);
        set_widthdrawn_cash(payment);
        set_profits(get_final_capital() - get_capital());
        std::cout << "Final capital without reinvestment: " << get_final_capital() << std::endl;
    }

    // Reinvestment strategy
    if (reinvest_status) {
        for (int i = get_index(); i < get_dates().size(); i += frequencey_pay) {
            float dividend = (get_close_prices()[i] * (0.03 / division_factor)) * num_shares;
            float extra_shares = dividend / get_close_prices()[i];
            num_shares += extra_shares;
            std::cout << "Dividend reinvested at index " << i << ", additional shares: " << extra_shares << std::endl;
        }

        float final_value = num_shares * get_close_prices().back();
        set_final_capital(final_value);
        set_profits(get_final_capital() - get_capital());
        set_widthdrawn_cash(0);
        std::cout << "Final capital with reinvestment: " << get_final_capital() << std::endl;
    }
}


bool Dividend::valid_pay_freq(string freq){

    if (freq == "Monthly"){
        set_pay_freq(freq);
        return true;
    }

    if (freq == "Quarterly"){
        set_pay_freq(freq);
        return true;
    }

    return false;

}


bool Dividend::valid_start_date(string start) {
    // Check if get_dates() is empty before accessing
    if (get_dates().empty()) {
        std::cerr << "Error: get_dates() is empty in valid_start_date." << std::endl;
        return false;
    }

    std::cout << "Validating start date: " << start << std::endl;

    string current_date = get_dates().back(); // Safe now because we checked if it's empty
    int index = 0;

    for (int i = 0; i < get_dates().size(); i++) {
        if (start == get_dates()[i]) {
            index = i;

            // Check for Monthly pay frequency
            if (get_pay_freq() == "Monthly" && (get_dates().size() - 1 - index >= 30)) {
                set_index(index);
                set_start_date(start);
                return true;
            }

            // Check for Quarterly pay frequency
            if (get_pay_freq() == "Quarterly" && (get_dates().size() - 1 - index >= 92)) {
                set_index(index);
                set_start_date(start);
                return true;
            }
        }
    }

    std::cerr << "Error: Start date not found or insufficient date range for the selected pay frequency." << std::endl;
    return false;
}


void Dividend::set_investment_type(){this->investment_type = "Dividend";}





