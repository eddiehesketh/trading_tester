#ifndef MOVINGAVERAGECROSSOVER_H
#define MOVINGAVERAGECROSSOVER_H

#include "Investment.h"
#include <vector>
#include <utility>
#include <string>

class MovingAverageCrossover : public Investment{
private:
    int shortPeriod;
    int longPeriod;
    std::vector<double> prices;
    std::vector<std::pair<int, std::string>> tradeSignals;
    double calculateSMA(int period);
    void executeStrategy();

public:
    MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod);
    void addPrice(double price);
    void displayTradeSignals();
    void investment_stratergy() override;
    bool valid_pay_freq(std::string freq) override;
    void set_investment_type() override; 
    int MovingAverage10D();
    int MovingAverage20D();
};

#endif