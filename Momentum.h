// Momentum is one of the investment strategies inherits to Investment

// Defining the class, and including the relevnat header files in the Investment class and ReadData class.
#ifndef MOMENTUM_H
#define MOMENTUM_H
#include "ReadData.h"
#include "Investment.h"

// Momentum publicly inheriting from investment.
class Momentum : public Investment{
public:
    // Momentum constructor, taking in a start date, initial amount of capital, stock name and the period of the momentum.
    Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period);

    // Override the valid pay frequency class.
    bool valid_pay_freq(std::string freq) override;

    // Override the set investment type class
    void set_investment_type() override;

    // Override the calculate momentum class.
    double calc_momentum(int period, int index_val) override;

    // Override the detect momentum class
    void detect_momentum() override;

    // Override the investment strategy class
    void investment_stratergy() override;

    // Override the finalise simulation class
    void finalise_simulation() override;
};

#endif