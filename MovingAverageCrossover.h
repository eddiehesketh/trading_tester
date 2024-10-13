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
    void large_period(int period1, int period2) override;
    double moving_average(int period, int currentIndex) override;
    void detect_crossover();
    void investment_stratergy() override;
    // int capitalToShares(double capital, double closePrice);
    // double sharesToCapital(int shares, double closePrice);
    void finalize_simulation() override;
    // int date_index(const std::vector<std::string>& dates, const std::string& _start_date) override;
};

#endif