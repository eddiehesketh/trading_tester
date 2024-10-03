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

    int index;

    for (int i = 0; i < get_dates().size(); i++){


        if (start == get_dates()[i]){

            index = i;

            if (get_pay_freq() == "Monthly"){

                if (get_dates().size()-1-index >= 30){

                    set_index(index);

                    set_start_date(start);

                    return true;
                }
            }

            if (get_pay_freq() == "Quarterly"){

                if (get_dates().size()-1-index >= 92){

                    set_index(index);

                    set_start_date(start);

                    return true;
                }
            }

            
        }
    }

}









