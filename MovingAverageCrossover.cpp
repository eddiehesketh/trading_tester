#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_) {
    this->Period1 = period1;
    this->Period2 = period2;
    isInvested = false;
    shares = 0;

    largePeriod(period1, period2);
    int index_val = longPeriod;
    set_investment_type();

    investment_stratergy();
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){
    return true;
}

void MovingAverageCrossover::set_investment_type() {
    this->investment_type = "Moving Average Crossover";
}

void MovingAverageCrossover::largePeriod(int period1, int period2) {
    if (period1 > period2) {
        longPeriod = period1;
        shortPeriod = period2;
    } else {
        longPeriod = period2;
        shortPeriod = period1;
    }
}

double MovingAverageCrossover::MovingAverage(int period, int index_val) {
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0;

    // Calculate the sum of the prices for the moving average
    for (int i = index_val; i > index_val - period; i++) {
        sum += close_stock[i]; // Use closePrices instead of prices
    }

    return sum / period; // Return the calculated moving average
}

void MovingAverageCrossover::detectCrossover() {
    const std::vector<float>& close_stock = get_close_prices();
    
    // Initialize previous MAs using the appropriate indices
    double previousShortMA = 0;
    double previousLongMA = 0;

    for (int index_val; index_val < close_stock.size(); index_val++) {
        // Calculate the current moving averages for the current index
        double shortMA = MovingAverage(shortPeriod, index_val);
        double longMA = MovingAverage(longPeriod, index_val);

        // Check for buy signal
        if (!isInvested && (previousShortMA <= previousLongMA && shortMA > longMA && previousShortMA !=0)) {
            std::cout << "Buy signal on " << (index_val - longPeriod + 1) << ": Short MA " << shortMA << " crossed above Long MA " << longMA << " Previous Short MA " << previousShortMA << " Previous Long MA " << previousLongMA << std::endl;
            isInvested = true;

            int sharesToBuy = capitalToShares(get_capital(), close_stock[index_val]);
            if (sharesToBuy > 0) {
                double cost = sharesToCapital(sharesToBuy, close_stock[index_val]);
                if (cost > capital) {
                    std::cerr << "Not enough capital to buy " << sharesToBuy << " shares." << std::endl;
                } else {
                    shares += sharesToBuy;
                    capital -= cost;
                    std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
                }
            } else {
                std::cout << "No shares can be bought due to insufficient capital or price." << std::endl;
            }
        } 
        // Check for sell signal
        else if (isInvested && (previousShortMA >= previousLongMA && shortMA < longMA)) {
            std::cout << "Sell signal on Day " << (index_val - longPeriod + 1) << ": Short MA " << shortMA << " crossed below Long MA " << longMA << " Previous Short MA " << previousShortMA << " Previous Long MA " << previousLongMA << std::endl;
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

void MovingAverageCrossover::investment_stratergy() {
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << get_capital() << std::endl;
    
    detectCrossover();

    finalizeSimulation();
}

int MovingAverageCrossover::capitalToShares(double capital, double closePrice) {
    if (capital <= 0) {
        std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
        return 0;
    }
    return static_cast<int>(capital / closePrice);
}

double MovingAverageCrossover::sharesToCapital(int shares, double closePrice) {
    if (shares <= 0) {
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
        return 0.0;
    }
    return shares * closePrice;
}

void MovingAverageCrossover::finalizeSimulation() {
    if (isInvested && shares > 0) {
        double lastClosePrice = stock_close.back();
        double finalCapital = sharesToCapital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        std::cout << "Final capital: $" << finalCapital << std::endl;
        capital += finalCapital;
        shares = 0;
    } else {
        std::cout << "Final capital: $" << capital << std::endl;
    }
}
