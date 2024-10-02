#include "Dividend.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;


Dividend::Dividend(string start_date_, float initial_capital, string pay_freq_, string stock_info, bool status):Investment(capital, stock_info), reinvest_status(status){

    if ((valid_start_date(start_date_)) && (valid_pay_freq(pay_freq_))){

    }

}

void Dividend::investment_stratergy(){


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


bool Dividend::valid_start_date(string start){

    string current_date = get_dates().back();

    

}









