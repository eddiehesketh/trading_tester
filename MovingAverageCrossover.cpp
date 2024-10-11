#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){
    shares = 0;
    this->Period1 = period1;
    this->Period2 = period2;

    largePeriod(period1, period2);
    set_investment_type();
    set_pay_freq("Once off");

    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){
    freq == "Once off";
    return true;
}

void MovingAverageCrossover::set_investment_type(){
    this->investment_type = "Moving Average Crossover";
}

void MovingAverageCrossover::largePeriod(int period1, int period2){
    if (period1 > period2) {
        longPeriod = period1;
        shortPeriod = period2;
    } else {
        longPeriod = period2;
        shortPeriod = period1;
    }
}

double MovingAverageCrossover::MovingAverage(int period){
    double sum = 0.0;
    if (prices.size() < period) {
        throw std::out_of_range("Not enough data to calculate moving average.");
    }
    for (size_t i = prices.size() - period; i < prices.size(); ++i){
        sum += prices[i];
    }
    return sum / period;
}

void MovingAverageCrossover::addPrice(double price){
    prices.push_back(price);
    if (prices.size() >= longPeriod){
        detectCrossover();
    }
}

void MovingAverageCrossover::detectCrossover(){
    if (prices.size() < longPeriod) return;

    double shortMA = MovingAverage(shortPeriod);
    double longMA = MovingAverage(longPeriod);
    static double previousShortMA = 0.0;
    static double previousLongMA = 0.0;

    if (previousShortMA != 0.0 && previousLongMA != 0.0){
        // Buy signal
        if (previousShortMA <= previousLongMA && shortMA > longMA && !isInvested){
            int day = prices.size();
            std::cout << "Buy signal on Day " << day << ": Short MA " << shortMA << " crossed above Long MA " << longMA << std::endl;
            isInvested = true;
            int sharesToBuy = capitalToShares(get_capital(), prices.back()); // Calculate how many shares to buy
            double cost = sharesToCapital(sharesToBuy, prices.back()); // Get the total cost for those shares
            if (cost > capital) {
                std::cerr << "Not enough capital to buy shares." << std::endl;
            } else {
                shares += sharesToBuy; // Update shares
                capital -= cost; // Deduct the cost of the shares from capital
                std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
            }
        }
        // Sell signal
        else if (previousShortMA >= previousLongMA && shortMA < longMA && isInvested){
            int day = prices.size();
            std::cout << "Sell signal on Day " << day << ": Short MA " << shortMA << " crossed below Long MA " << longMA << std::endl;
            isInvested = false;
            double earnings = sharesToCapital(shares, prices.back()); // Sell all shares based on the latest closing price
            capital += earnings; // Update capital with the earnings from selling shares
            std::cout << "Sold all shares." << " Capital: " << capital << std::endl;
            shares = 0; // Reset shares to 0 after selling
        }
    }

    // Update previous values
    previousShortMA = shortMA;
    previousLongMA = longMA;
}

void MovingAverageCrossover::loadPricesFromCSV() {

    // Get the close prices from the CSV
    const std::vector<float>& closePrices = readData.get_close_prices();
    
    // Loop through each price and add it to the MovingAverageCrossover object
    for (double price : closePrices) {
        addPrice(price);
    }
}

void MovingAverageCrossover::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << get_capital() << std::endl;
    loadPricesFromCSV();
    finalizeSimulation();
}

int MovingAverageCrossover::capitalToShares(double capital, double closePrice){
    return static_cast<int>(capital / closePrice);
}

double MovingAverageCrossover::sharesToCapital(int shares, double closePrice){
    if (shares < 0){
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
        return 0.0;
    }
    return shares * closePrice;
}

void MovingAverageCrossover::finalizeSimulation(){
    if (isInvested && shares > 0){
        double lastClosePrice = prices.back();
        double finalCapital = sharesToCapital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        std::cout << "Final capital from selling shares: $" << finalCapital << std::endl;
        capital += finalCapital;
        shares = 0;
    }
}