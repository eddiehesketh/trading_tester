#ifndef MOVINGAVERAGECROSSOVER_H
#define MOVINGAVERAGECROSSOVER_H
#include "ReadData.h"
#include "Investment.h"
#include <vector>
#include <utility>
#include <string>

class MovingAverageCrossover : public Investment {
public:
    MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2);
    bool valid_pay_freq(std::string freq) override;
    void set_investment_type() override; 
    void largePeriod(int period1, int period2);
    double MovingAverage(int period, int currentIndex);
    void detectCrossover();
    void investment_stratergy() override;
    // int capitalToShares(double capital, double closePrice);
    // double sharesToCapital(int shares, double closePrice);
    void finalizeSimulation() override;
};

#endif