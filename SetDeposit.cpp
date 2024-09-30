#include "SetDeposit.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;

SetDeposit::SetDeposit(string _start_date, string stock_info, int capital): ReadData(stock_info), Investment(capital){

    if (!start_date(_start_date)){
        return;
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


bool SetDeposit::start_date(string _start_date){

    for (int i = 0; i < get_dates().size(); i++){

        if (_start_date.compare(get_dates()[i])){
            set_index(i);

            return true;
        }
    }

    return false;

}

void SetDeposit::set_index(int _index){this->index = _index;}

int SetDeposit::get_index(){return this->index;}

void SetDeposit::set_final_capital(int _capital){this->final_capital = _capital;}

void SetDeposit::set_profits(float _profits){this->profits = _profits;}






