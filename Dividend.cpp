// Including the relevant libraries.
#include "Dividend.h"
#include "ReadData.h"
#include <iostream> 
#include <string>

// Using the standard namespace.
using namespace std;

// Dividend contructor, calling the investment constructor with the initial capital and start date.
Dividend::Dividend(string start_date_, float initial_capital, string pay_freq_, string stock_info, bool status):Investment(initial_capital, stock_info){

    // Setting the reinvestment status.
    set_reivest_status(status);

    // Setting the investment type.
    set_investment_type();

    // Initialising the final capital.
    set_final_capital(0);

    // Checking if the pay frequencey is valid.
    if (valid_pay_freq(pay_freq_)){

        // If so, checking if the start date is valid.
        if (valid_start_date(start_date_)){
            investment_stratergy(); // Calling the investment stratergy.
        }
    }

    std::cout << "In Dividend constructor, get_dates().size() = " << get_dates().size() << std::endl;


}

// Overriding the investment stratergy and re-implementing it.
void Dividend::investment_stratergy() {

    // Calculating the number of shares based on the capital and close price at the given index.
    float num_shares = get_capital() / get_close_prices()[get_index()];

    // Initalisng other variables.
    float payment = 0;
    int frequencey_pay = 0;
    float division_factor = 1.0;

    // Checking the pay frequencey.
    if (get_pay_freq() == "Monthly"){

        // If monthly set the pay frequencey to 30, and division factor to 12.
        frequencey_pay = 30;
        division_factor = 12;

    } else if (get_pay_freq() == "Quarterly"){

        // If set to quarterly, set pay frequencey to 92 and the division factor to 4.
        frequencey_pay = 92;
        division_factor = 4;

    }
    

    // Checking the reinvestment status, to determine which investment apporach to take.
    if (!reinvest_status){

        // If not reinvesting, calculate the payment based on initial capital.
        payment = get_capital();

        // Loop through each date starting from the investment start date.
        for (int i = get_index(); i < get_dates().size(); i++){

            // Calculate the daily dividend based on a 3% annual rate and the number of shares owned.
            float dividend = (get_close_prices()[i]*(0.03)/365)*num_shares;

            // Add the dividend to the total payment.
            payment = payment + dividend;
        }

        // Set the final capital to the total payment and initial capital.
        set_final_capital(payment + get_capital());

        // Record the total withdrawn cash as the final payment.
        set_widthdrawn_cash(payment);

        // Calculate and set the profits by subtracting the initial capital from the final capital.
        set_profits(get_final_capital()-get_capital());
    }

    // If reinvesting dividends, compound the number of shares instead of taking payments.
    if (reinvest_status) {
        
         // Loop through each date, reinvesting dividends at regular intervals, such as monthly or quarterly.
        for (int i = get_index(); i < get_dates().size(); i += frequencey_pay) {

            // Calculate the dividend for the current period.
            float dividend = (get_close_prices()[i] * (0.03 / division_factor)) * num_shares;

            // Calculate the additional shares that can be purchased with the dividend.
            float extra_shares = dividend / get_close_prices()[i];

            // Add the newly purchased shares to the total number of shares.
            num_shares += extra_shares;
        }

        // Calculate the final value of the investment based on the total shares owned and the closing price.
        float final_value = num_shares * get_close_prices().back();

        // Set the final capital based on the value of the shares.
        set_final_capital(final_value);

        // Calculate and set the profits by subtracting the initial capital from the final capital.
        set_profits(get_final_capital()-get_capital());

        // Set the withdrawn cash to zero since dividends were reinvested.
        set_widthdrawn_cash(0);
    }



}

// Validate the payment frequency, overriding and re-implementing it.
bool Dividend::valid_pay_freq(string freq){

    // If the payment frequency is Monthly, set the payment frequency and return true.
    if (freq == "Monthly"){
        set_pay_freq(freq);
        return true;
    }

    // If the payment frequency is Quarterly, set the payment frequency and return true.
    if (freq == "Quarterly"){
        set_pay_freq(freq);
        return true;
    }

    // If neither, don't set anything and return false.
    return false;

}

// Validate the start date for the dividend strategy.
bool Dividend::valid_start_date(string start) {
    // Check if get_dates() is empty before accessing
    if (get_dates().empty()) {
        std::cerr << "Error: get_dates() is empty in valid_start_date for stock " << name << std::endl;
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


// Set the type of investment to Dividend.
void Dividend::set_investment_type(){this->investment_type = "Dividend";}