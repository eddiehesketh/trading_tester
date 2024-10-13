#include "Momentum.h"
#include <iostream>

Momentum::Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info){
    this->period = period;
    shares = 0;

    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

bool Momentum::valid_pay_freq(std::string freq){
    return true;
}

void Momentum::set_investment_type() {
    this->investment_type = "Momentum";
}

double Momentum::calcMomentum(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0; 
    sum = close_stock[index_val] - close_stock[index_val - period + 1];
    return sum;
}

void Momentum::detectMomentum(){
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& current_date = get_dates();
    
    // Set conditions
    int index_val = period - 1;
    isInvested = false;

    for (; index_val < close_stock.size(); index_val++){
        // Calculate the current moving averages for the current index
        double momentum = calcMomentum(period, index_val);

        // Check for buy signal
        if (!isInvested && (momentum >= 0)){
            std::cout << "Buy signal on " << current_date[index_val] << ": Momentum " << momentum << std::endl;
            isInvested = true;

            // Check for purchase shares
            int sharesToBuy = capitalToShares(get_capital(), close_stock[index_val]);
            if (sharesToBuy > 0){
                double cost = sharesToCapital(sharesToBuy, close_stock[index_val]);
                if (cost > capital){
                    std::cerr << "Not enough capital to buy shares." << std::endl;
                    isInvested = false;
                } else {
                    // Buy shares
                    shares += sharesToBuy;
                    capital -= cost;
                    std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
                    sharesToBuy = 0;
                    cost = 0;
                }
            } else{
                std::cout << "No shares can be bought" << std::endl;
            }
        } 
        // Check for sell signal
        else if (isInvested && momentum < 0){
            std::cout << "Sell signal on " << current_date[index_val] << ": Momentum " << momentum << std::endl;
            
            // Sell shares
            isInvested = false;
            double earnings = sharesToCapital(shares, close_stock[index_val]);
            capital += earnings;
            std::cout << "Sold all shares. Capital: " << capital << std::endl;
            shares = 0;
        }
    }
}

void Momentum::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << get_capital() << std::endl;

    // Runs dectection and finalisation of the strategy
    detectMomentum();
    finalizeSimulation();
}

int Momentum::capitalToShares(double capital, double closePrice){
    // Determines if shares can be bought
    if (capital <= 0){
        std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
        return 0;
    }
    // Returns number of purchasable shares
    return static_cast<int>(capital / closePrice);
}

double Momentum::sharesToCapital(int shares, double closePrice){
    // Determines if shares can be sold
    if (shares <= 0){
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
        return 0.0;
    }
    // Returns number of sellable shares
    return shares * closePrice;
}
void Momentum::finalizeSimulation(){
    // Sells all remaining shares 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back();
        double finalCapital = sharesToCapital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        std::cout << "Final capital: $" << finalCapital << std::endl;
        capital += finalCapital;
        shares = 0;
    } else{
        std::cout << "Final capital: $" << capital << std::endl;
    }
}
