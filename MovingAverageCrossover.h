#ifndef MOVINGAVERAGECROSSOVER_H
#define MOVINGAVERAGECROSSOVER_H

#include "Investment.h"
#include <vector>
#include <utility>
#include <string>

class MovingAverageCrossover : public Investment {
public:
    MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod);
    void addPrice(double price);
    void displayTradeSignals();
    void investment_stratergy() override;
    bool valid_pay_freq(std::string freq) override;
    void set_investment_type() override; 
    double MovingAverage(int period); // Generalized moving average function
    double MovingAverage10D(); // Specific for 10-day moving average
    double MovingAverage20D(); // Specific for 20-day moving average
    double calculateSMA(int period);
    void executeStrategy();
};

#endif