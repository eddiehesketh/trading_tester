#include "Dividend.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;


Dividend::Dividend(string start_date_, float initial_capital, string pay_freq_, string stock_info, bool status):Investment(initial_capital, stock_info), reinvest_status(status){

    set_final_capital(0);

    if (valid_pay_freq(pay_freq_)){

        if (valid_start_date(start_date_)){
            investment_stratergy();
        }
    }

}

void Dividend::investment_stratergy() {

    float num_shares = get_capital() / get_close_prices()[get_index()];

    float payment = 0;

    int frequencey_pay = 0;
    float division_factor = 1.0;

    if (get_pay_freq() == "Monthly"){

        frequencey_pay = 30;
        division_factor = 12;
    } else if (get_pay_freq() == "Quarterly"){
        frequencey_pay = 92;
        division_factor = 4;

    }
    


    if (!reinvest_status){

        for (int i = get_index(); i < get_dates().size(); i++){

            float dividend = (get_close_prices()[i]*(0.03)/365)*num_shares;

            payment = payment + dividend;
        }

        set_final_capital(payment);
        set_widthdrawn_cash(payment);
    }

    if (reinvest_status) {
        // With reinvestment, compound shares
        for (int i = get_index(); i < get_dates().size(); i += frequencey_pay) {
            float dividend = (get_close_prices()[i] * (0.03 / division_factor)) * num_shares;
            float extra_shares = dividend / get_close_prices()[i];
            num_shares += extra_shares;
        }

        float final_value = num_shares * get_close_prices().back();
        set_final_capital(final_value);
        set_widthdrawn_cash(0);
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


bool Dividend::valid_start_date(string start){

    string current_date = get_dates().back();

    int index = 0;

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

    return false;

}





