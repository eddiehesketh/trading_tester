#ifndef MEANREVERSIONS_H
#define MEANREVERSIONS_H

#include "Investment.h"

class Momentum : public Investment{
public:
    Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period);
    void investment_stratergy() override; 
    bool valid_pay_freq(std::string freq) override;
    void set_investment_type() override; 
    void displayTradeSignals(); 
    void addPrice(double price); 
};

#endif