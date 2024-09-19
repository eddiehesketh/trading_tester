#include "SetDeposit.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;

SetDeposit::SetDeposit(string _start_date, string stock_info): ReadData(stock_info){

    if (!start_date(_start_date)){
        return;
    } 

    

    



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






