#include "Momentum.h"
#include <iostream>
#include <vector>
#include <string>

Momentum::Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info){
    set_investment_type();
    set_pay_freq("Once off");
    this->period = period;
    this-> start_date_ = _start_date;
    this->moving_capital = capital;
    shares = 0;

    if (valid_start_date(start_date_)){
        investment_stratergy();
    } else{
        std::cout << "Non-existant start date" << std::endl;
    }
}

bool Momentum::valid_pay_freq(std::string freq){
    // Checks if the frequencey is once off.
    if (freq == "Once off"){

        // If so return true.
        return true; 
    }
    // If not return false.
    return false;
}

void Momentum::set_investment_type() {
    this->investment_type = "Momentum";
}

double Momentum::calc_momentum(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0; 
    
    if (index_val < period - 1){
        return 1000000;
    }

    sum = close_stock[index_val] - close_stock[index_val - period + 1];
    return sum;
}

void Momentum::detect_momentum(){
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();
    
    // Set conditions
    isInvested = false;
    int index_val = date_index(dates, start_date_);
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{
        for (; index_val < close_stock.size(); index_val++){
            // Calculate the current moving averages for the current index
            double momentum = calc_momentum(period, index_val);
            if (momentum == 1000000){
            std::cout << "Invalid start date" << std::endl;
            break;
            }
            // Check for buy signal
            if (!isInvested && (momentum >= 0)){
                std::cout << "Buy signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
                isInvested = true;

                // Check for purchase shares
                int sharesToBuy = capital_to_shares(moving_capital, close_stock[index_val]);
                if (sharesToBuy > 0){
                    double cost = shares_to_capital(sharesToBuy, close_stock[index_val]);
                    if (cost > moving_capital){
                        std::cerr << "Not enough capital to buy shares." << std::endl;
                        isInvested = false;
                    } else{
                        // Buy shares
                        shares += sharesToBuy;
                        moving_capital -= cost;
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
                std::cout << "Sell signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
            
                // Sell shares
                isInvested = false;
                double earnings = shares_to_capital(shares, close_stock[index_val]);
                moving_capital += earnings;
                std::cout << "Sold all shares. Capital: " << moving_capital << std::endl;
                shares = 0;
            }
        }
    }
}

void Momentum::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << capital << std::endl;

    // Runs dectection and finalisation of the strategy
    detect_momentum();
    finalise_simulation();
}

void Momentum::finalise_simulation(){
    // Sells all remaining shares 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back();
        double finalEarnings = shares_to_capital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        moving_capital += finalEarnings;
        final_capital = moving_capital;
        std::cout << "Final capital: $" << final_capital << std::endl;
        shares = 0;
    } else{
        final_capital = moving_capital;
        std::cout << "Final capital: $" << final_capital << std::endl;
    }
    profits = final_capital - capital;
    set_profits(profits);
}