#include "Dividend.h"
#include "ReadData.h"
#include <iostream>
#include <string>

using namespace std;


Dividend::Dividend(string start_date_, float initial_capital, string pay_freq_, string stock_info, bool status):Investment(initial_capital, stock_info), reinvest_status(status){

    this->dividend_yield = 3.0f;

    if ((valid_start_date(start_date_)) && (valid_pay_freq(pay_freq_))){

        investment_stratergy();

    }

}

void Dividend::investment_stratergy(){

    float buy_price = get_close_prices()[get_index()];

    float num_shares = get_capital()/ buy_price;

    int days_between_payments = 0;

    float total_dividend = 0;

    // float total_dividend = num_shares * dividend_per_share;

    if (get_pay_freq() == "Monthly"){
        
        days_between_payments = 30;

    } else if (get_pay_freq() == "Quarterly"){

        days_between_payments = 92;

    }



    for (int i = get_index(); i < get_dates().size(); i += days_between_payments){

        float dividend_per_share = get_close_prices()[i] * (this->dividend_yield / 100.0f);
        total_dividend += num_shares * dividend_per_share;


        if (reinvest_status){
            float additional_shares = total_dividend / get_close_prices()[i];

            num_shares += additional_shares;

            set_capital(num_shares * get_close_prices()[i]);

            set_widthdrawn_cash(0.0);

            total_dividend = 0; 

        } else if (!reinvest_status){

            float new_cash = get_widthdrawn_cash() + total_dividend;

            set_widthdrawn_cash(new_cash);

            set_capital(num_shares * get_close_prices()[i]);

            total_dividend = 0;
            
        }


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









