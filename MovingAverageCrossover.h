// MovingAverageCrossover is one of the investment strategies inherits to Investment

// Defining the class, and including the relevnat header files in the Investment class and ReadData class.
#ifndef MOVINGAVERAGECROSSOVER_H
#define MOVINGAVERAGECROSSOVER_H
#include "ReadData.h"
#include "Investment.h"

// Moving Average Crossover publicly inheriting from investment.
class MovingAverageCrossover : public Investment {
public:
    // Moving Average Crossover constructor, taking in a start date, initial amount of capital, stock name and the two moving average periods.
    MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2);

    // Overriding the valid pay frequencey class.
    bool valid_pay_freq(std::string freq) override;

    // Overriding the set investment type class.
    void set_investment_type() override;

    // Overriding the large period class.
    void large_period(int period1, int period2) override;

    // Overriding the moving average class.
    double moving_average(int period, int currentIndex) override;

    // Overriding the detect crossover class.
    void detect_crossover() override;
 
    // Overriding the pure investment stratergy class.
    void investment_stratergy() override;

    // Overriding the finalise simulation class
    void finalise_simulation() override;
};

#endif