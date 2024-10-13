#include "Investment.h"

using namespace std;

Investment::Investment(float initial_capital, string stock_info_):capital(initial_capital), invest_return(0), deposit_amount(0), index(0), 
                                                                    final_capital(0), profits(0),widthdrawn_cash(0), period(0), momentum(0), meanPrice(0), 
                                                                    Period1(0), Period2(0), shortPeriod(0), longPeriod(0), shares(0), invested_capital(0),
                                                                    ReadData(stock_info_){};




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


void Investment::set_pay_freq(string freq){this->pay_freq = freq;}

string Investment::get_pay_freq(){return this->pay_freq;}

void Investment::set_index(int _index){this->index = _index;}

int Investment::get_index(){return this->index;}

void Investment::set_final_capital(int _capital){this->final_capital = _capital;}

void Investment::set_profits(float _profits){this->profits = _profits;}

float Investment::get_final_capital(){return this->final_capital;}

void Investment::set_start_date(string _start_date){this->start_date_ = _start_date;}

void Investment::set_reivest_status(bool stat){this->reinvest_status = stat;}

void Investment::set_widthdrawn_cash(float v){this->widthdrawn_cash = v;}

float Investment::get_widthdrawn_cash(){return this->widthdrawn_cash;}

string Investment::get_investment_type(){return this->investment_type;}

float Investment::get_profits(){return this->profits;}

double Investment::calcMomentum(int period, int index_val){return 0;}

void Investment::detectMomentum(){};

int Investment::capitalToShares(double capital, double closePrice){
    // Determines if shares can be bought
    if (capital <= 0){
        std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
        return 0;
    }
    // Returns number of purchasable shares
    return static_cast<int>(capital / closePrice);
}


double Investment::sharesToCapital(int shares, double closePrice){
    // Determines if shares can be sold
    if (shares <= 0){
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
        return 0.0;
    }
    // Returns number of sellable shares
    return shares * closePrice;
}

void Investment::finalizeSimulation(){};

void Investment::largePeriod(int period1, int period2){};

double Investment::MovingAverage(int period, int currentIndex){return 0;}

void Investment::detectCrossover(){};





    // void largePeriod(int period1, int period2);
    // double MovingAverage(int period, int currentIndex);
    // void detectCrossover();