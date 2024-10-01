#include "Investment.h"

using namespace std;

Investment::Investment(float initial_capital, string stock_info_):capital(initial_capital), ReadData(stock_info_){};

// Investment::Investment():Investment(0){};

float Investment::get_capital(){return this->capital;}

void Investment::set_capital(float new_capital){this->capital = new_capital;} 



bool Investment::valid_start_date(string _start_date){

    for (int i = 0; i < get_dates().size(); i++){

        if (_start_date == get_dates()[i]){
            set_index(i);
            set_start_date(_start_date);

            return true;
        }
    }

    return false;

}

void Investment::set_index(int _index){this->index = _index;}

int Investment::get_index(){return this->index;}

void Investment::set_final_capital(int _capital){this->final_capital = _capital;}

void Investment::set_profits(float _profits){this->profits = _profits;}

float Investment::get_final_capital(){return this->final_capital;}

void Investment::set_start_date(string _start_date){this->start_date_ = _start_date;}