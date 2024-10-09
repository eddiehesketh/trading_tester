#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include "Investment.h"
#include <vector>
#include <utility>
#include <string>

class MovingAverage : public Investment{
public:
    MovingAverage(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod);
    void addPrice(double price);
    void displayTradeSignals();
    void investment_stratergy() override;
    bool valid_pay_freq(std::string freq) override; 

private:
    int shortPeriod;
    int longPeriod;
    std::vector<double> prices;
    std::vector<std::pair<int, std::string>> tradeSignals;

    double calculateSMA(int period);
    void executeStrategy();
};

#endif