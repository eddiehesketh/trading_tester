#ifndef MOMENTUM_H
#define MOMENTUM_H
#include "ReadData.h"
#include "Investment.h"
#include <vector>
#include <utility>
#include <string>
#include <optional>
#include <numeric>

class Momentum : public Investment{
    public:
        Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period);
        bool valid_pay_freq(std::string freq) override;
        void set_investment_type() override; 
        double calcMomentum(int period, int index_val) override; 
        void detectMomentum() override;
        void investment_stratergy() override;
        // // int capitalToShares(double capital, double closePrice);
        // double sharesToCapital(int shares, double closePrice);
        void finalizeSimulation() override;
};

#endif