#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){
    this->Period1 = period1;
    this->Period2 = period2;
    shares = 0;

    largePeriod(period1, period2);
    set_investment_type();   
    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){
    return true;
}

void MovingAverageCrossover::set_investment_type() {
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

double MovingAverageCrossover::MovingAverage(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0;

    // Calculate the sum of the prices for the moving average
    for (int i = index_val; i >= (index_val - period + 1); i--){
        sum += close_stock[i]; // Use closePrices instead of prices
    }

    return sum / period; // Return the calculated moving average
}

void MovingAverageCrossover::detectCrossover(){
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& current_date = get_dates();

    // Set conditions
    double previousShortMA = 0;
    double previousLongMA = 0;
    int index_val = longPeriod - 1;
    isInvested = false;

    for (; index_val < close_stock.size(); index_val++){
        // Calculate the current moving averages for the current index
        double shortMA = MovingAverage(shortPeriod, index_val);
        double longMA = MovingAverage(longPeriod, index_val);

        // Check for buy signal
        if (!isInvested && (previousShortMA <= previousLongMA && shortMA > longMA && previousShortMA !=0)){
            std::cout << "Buy signal on " << current_date[index_val] << ": ShortMA " << shortMA << " crossed above LongMA " << longMA << " Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
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
            std::cout << "Sell signal on " << current_date[index_val] << ": ShortMA " << shortMA << " crossed below LongMA " << longMA << " Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
            
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

void MovingAverageCrossover::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << get_capital() << std::endl;
    
    detectCrossover();
    finalizeSimulation();
}

int MovingAverageCrossover::capitalToShares(double capital, double closePrice){
    if (capital <= 0){
        std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
        return 0;
    }
    return static_cast<int>(capital / closePrice);
}

double MovingAverageCrossover::sharesToCapital(int shares, double closePrice){
    if (shares <= 0){
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
        return 0.0;
    }
    return shares * closePrice;
}

void MovingAverageCrossover::finalizeSimulation(){
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
