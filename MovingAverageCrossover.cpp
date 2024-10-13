#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){
    this->Period1 = period1;
    this->Period2 = period2;
    this-> start_date_ = _start_date;
    shares = 0;

    largePeriod(period1, period2);
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

void MovingAverageCrossover::largePeriod(int period1, int period2){
    // Of the two period inputs determine which is larger
    if (period1 > period2) {
        longPeriod = period1;
        shortPeriod = period2;
    } else {
        longPeriod = period2;
        shortPeriod = period1;
    }
}

int MovingAverageCrossover::dateIndex(const std::vector<std::string>& dates, const std::string& _start_date){
    for (int i = 0; i < dates.size(); i++){
        if (dates[i] == _start_date) {
            return i;
        }
    }
    return -1;
}

double MovingAverageCrossover::MovingAverage(int period, int index_val){
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

void MovingAverageCrossover::detectCrossover(){
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();

    // Set conditions
    double previousShortMA = 0;
    double previousLongMA = 0;
    isInvested = false;
    int index_val = dateIndex(dates, start_date_);
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{
        // Iterate through all moving averages
        for (; index_val < close_stock.size(); index_val++){
            // Calculate the current moving averages for the current index
            double shortMA = MovingAverage(shortPeriod, index_val);
            double longMA = MovingAverage(longPeriod, index_val);
            if (shortMA == 1000000 || longMA == 1000000){
                std::cout << "Invalid start date" << std::endl;
                break;
            }
            // Check for buy signal
            if (!isInvested && (previousShortMA <= previousLongMA && shortMA > longMA && previousShortMA !=0)){
                std::cout << "Buy signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed above LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
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
            else if (isInvested && (previousShortMA >= previousLongMA && shortMA < longMA)){
                std::cout << "Sell signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed below LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
            
                // Sell shares
                isInvested = false;
                double earnings = sharesToCapital(shares, close_stock[index_val]);
                capital += earnings;
                std::cout << "Sold all shares. Capital: " << capital << std::endl;
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
    std::cout << "Initial capital: " << get_capital() << std::endl;
    
    // Runs dectection and finalisation of the strategy
    detectCrossover();
    finalizeSimulation();
}

// int MovingAverageCrossover::capitalToShares(double capital, double closePrice){
//     // Determines if shares can be bought
//     if (capital <= 0){
//         std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
//         return 0;
//     }
//     // Returns number of purchasable shares
//     return static_cast<int>(capital / closePrice);
// }

// double MovingAverageCrossover::sharesToCapital(int shares, double closePrice){
//     // Determines if shares can be sold
//     if (shares <= 0){
//         std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
//         return 0.0;
//     }
//     // Returns number of sellable shares
//     return shares * closePrice;
// }

void MovingAverageCrossover::finalizeSimulation(){
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
