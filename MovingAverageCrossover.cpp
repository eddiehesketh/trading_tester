#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){

    this->Period1 = period1;
    this->Period2 = period2;

    largePeriod(Period1, Period2);
    set_investment_type();
    set_pay_freq("Once off");
    if (valid_start_date(_start_date)) {
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

void MovingAverageCrossover::largePeriod(int period1, int period2) {
    if (period1 > period2) {
        longPeriod = period1;
        shortPeriod = period2;
    } else {
        longPeriod = period2;
        shortPeriod = period1;
    }
}

double MovingAverageCrossover::MovingAverage(int period) {
    if (prices.size() < period) {
        throw std::out_of_range("Not enough data to calculate moving average.");
    }
    
    double sum = 0.0;

    for (size_t i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }

    return sum / period;
}

void MovingAverageCrossover::addPrice(double price){
    prices.push_back(price);
    if (prices.size() >= Period2) {
        detectCrossover();
    }
}

void MovingAverageCrossover::detectCrossover(){
    if (prices.size() < longPeriod) return;

    // Calculate MA's
    double shortMA = MovingAverage(shortPeriod);
    double longMA = MovingAverage(longPeriod);
    // Store previous MA's
    static double previousShortMA = 0.0; 
    static double previousLongMA = 0.0;

    // Check for crossover
    if (previousShortMA != 0.0 && previousLongMA != 0.0) {
        // Buy signal (shortMA crosses above longMA)
        if (previousShortMA <= previousLongMA && shortMA > longMA) {
            int day = prices.size();
            std::cout << "Buy signal on Day " << day << ": Short MA " << shortMA << " crossed above Long MA " << longMA << std::endl;
        }
        // Sell signal (shortMA crosses below longMA)
        else if (previousShortMA >= previousLongMA && shortMA < longMA) {
            int day = prices.size();
            std::cout << "Sell signal on Day " << day << ": Short MA " << shortMA << " crossed below Long MA " << longMA << std::endl;
        }
    }

    // Update previous values
    previousShortMA = shortMA;
    previousLongMA = longMA;
}

void MovingAverageCrossover::loadPricesFromCSV(const std::string& filename){
    ReadData readData(filename);
    const std::vector<float>& closePrices = readData.get_close_prices();

    for (double price : closePrices) {
        addPrice(price);
    }
}

void MovingAverageCrossover::investment_stratergy(){
    loadPricesFromCSV("MA.csv");
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Current capital: " << get_capital() << std::endl;
    detectCrossover();
}
