#include "SetDeposit.h"
#include "ReadData.h"
#include <iostream>
#include <string>

// Informing the program that the standard namespace will be used.
using namespace std;

// Set Deposit constuctor, taking in a start data, stock info, and capital amount.
SetDeposit::SetDeposit(string _start_date, string stock_info, int capital): Investment(capital, stock_info){

    // Setting the investment type from the constructor.
    set_investment_type();

    // Setting the pay frequency to once off.
    set_pay_freq("Once off");

    // Setting the reinvestment status to false.
    set_reivest_status(false);

    // Checking if there is a valid start date.
    if (valid_start_date(_start_date)){

        // if there is a valid start date, the investment stratergy is called.
        investment_stratergy();
    }
     

}

// Default constructor.
SetDeposit::SetDeposit():SetDeposit(NULL, NULL, 0){};

// Implementing the overidden investment stratergy function.
void SetDeposit::investment_stratergy(){

    // Initalisng required variables.
    float num_shares = 0; // Number of shares.
    float current_price = 0; // Current price of shares.
    float profit = 0; // Profits.
    float new_capital = 0; // New capital.

    // Calculating the current price based off the most recent day of the avaliable data.
    current_price = get_open_prices()[get_open_prices().size()-1];

    // Calulating the number of shares that can be bought with the capital given at the given start date.
    num_shares = get_capital() / get_open_prices()[get_index()];

    // Calulating the new capital based off the most recent price and number of shares owned.
    new_capital = num_shares*current_price;

    // Calculating the profit based off the investment.
    profit = new_capital - get_capital();

    // Setting the final capital.
    set_final_capital(new_capital);

    // Seting the profits.
    set_profits(profit);

}

// Valid pay freuqnecey function.
bool SetDeposit::valid_pay_freq(string freq){

    // Checks if the frequencey is once off.
    if (freq == "Once off"){

        // If so return true.
        return true; 
    }

    // If not return false.
    return false;
}

// Setting investment type to deposit.
void SetDeposit::set_investment_type(){this->investment_type = "Deposit";}










