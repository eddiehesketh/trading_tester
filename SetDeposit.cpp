#include "SetDeposit.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;

SetDeposit::SetDeposit(string _start_date, string stock_info, int capital): Investment(capital, stock_info){

    set_investment_type();
    set_pay_freq("Once off");
    set_reivest_status(false);

    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
     

}

void SetDeposit::investment_stratergy(){

    float num_shares = 0;
    float current_price = 0;
    float profit = 0;
    float new_capital = 0;


    current_price = get_open_prices()[get_open_prices().size()-1];

    num_shares = get_capital() / get_open_prices()[get_index()];

    new_capital = num_shares*current_price;

    profit = new_capital - get_capital();

    set_final_capital(new_capital);

    set_profits(profit);

}

 bool SetDeposit::valid_pay_freq(string freq){

    if (freq == "Once off"){
        return true;
    }

    return false;
}

void SetDeposit::set_investment_type(){this->investment_type = "Deposit";}










