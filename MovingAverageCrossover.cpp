#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){
    set_investment_type();
    this->Period1 = period1;
    this->Period2 = period2;
    this->start_date_ = _start_date;
    this->moving_capital = capital;
    shares = 0;

    large_period(period1, period2);
    if (valid_start_date(start_date_)){
        investment_stratergy();
    } else{
        std::cout << "Non-existant start date" << std::endl;
    }
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){
    return true;
}

void MovingAverageCrossover::set_investment_type(){
    this->investment_type = "Moving Average Crossover";
}

void MovingAverageCrossover::large_period(int period1, int period2){
    // Of the two period inputs determine which is larger
    if (period1 > period2) {
        longPeriod = period1;
        shortPeriod = period2;
    } else {
        longPeriod = period2;
        shortPeriod = period1;
    }
}

double MovingAverageCrossover::moving_average(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0;

    if (index_val < period - 1){
        return 1000000;
    }
    // Calculate and return the sum of the prices for the moving average
    for (int i = index_val; i >= (index_val - period + 1); i--){
        sum += close_stock[i]; // Use closePrices instead of prices
    }
    return sum / period;
}

void MovingAverageCrossover::detect_crossover(){
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();

    // Set conditions
    double previousShortMA = 0;
    double previousLongMA = 0;
    isInvested = false;
    int index_val = date_index(dates, start_date_);
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{
        // Iterate through all moving averages
        for (; index_val < close_stock.size(); index_val++){
            // Calculate the current moving averages for the current index
            double shortMA = moving_average(shortPeriod, index_val);
            double longMA = moving_average(longPeriod, index_val);
            if (shortMA == 1000000 || longMA == 1000000){
                std::cout << "Invalid start date" << std::endl;
                break;
            }
            // Check for buy signal
            if (!isInvested && (previousShortMA <= previousLongMA && shortMA > longMA && previousShortMA !=0)){
                std::cout << "Buy signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed above LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
                isInvested = true;

                // Check for purchase shares
                int sharesToBuy = capital_to_shares(moving_capital, close_stock[index_val]);
                if (sharesToBuy > 0){
                    double cost = shares_to_capital(sharesToBuy, close_stock[index_val]);
                    if (cost > moving_capital){
                        std::cerr << "Not enough capital to buy shares." << std::endl;
                        isInvested = false;
                    } else {
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
            else if (isInvested && (previousShortMA >= previousLongMA && shortMA < longMA)){
                std::cout << "Sell signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed below LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
            
                // Sell shares
                isInvested = false;
                double earnings = shares_to_capital(shares, close_stock[index_val]);
                moving_capital += earnings;
                std::cout << "Sold all shares. Capital: " << moving_capital << std::endl;
                shares = 0;
            }

            // Update previous moving averages for the next iteration
            previousShortMA = shortMA;
            previousLongMA = longMA;
        }
    }
}

void MovingAverageCrossover::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << capital << std::endl;
    
    // Runs dectection and finalisation of the strategy
    detect_crossover();
    finalise_simulation();
}

void MovingAverageCrossover::finalise_simulation(){
    // Sells all remaining shares 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back();
        double finalEarnings = shares_to_capital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital" << std::endl;
        moving_capital += finalEarnings;
        final_capital = moving_capital;
        std::cout << "Final capital: $" << final_capital << std::endl;
        shares = 0;
    } else{
        final_capital = moving_capital;
        std::cout << "Final capital: $" << final_capital << std::endl;
    }
}