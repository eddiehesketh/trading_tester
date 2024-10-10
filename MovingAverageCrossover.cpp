#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int Period1, int Period2)
    : Investment(initial_capital, stock_info_) {
    this->Period1 = Period1;
    this->Period2 = Period2;
    if (valid_start_date(_start_date)) {
        return;
    }
}

void MovingAverageCrossover::largePeriod(int Period1, int Period2) {
    if (Period1 > Period2){
        longPeriod = Period1;
        shortPeriod = Period2;
    } else {
        longPeriod = Period2;
        shortPeriod = Period1;
    }
}

void MovingAverageCrossover::addPrice(double price) {
    prices.push_back(price);
    if (prices.size() >= Period2) {
        executeStrategy();
    }
}

void MovingAverageCrossover::displayTradeSignals() {
    for (const auto& signal : tradeSignals) {
        std::cout << "Day " << signal.first << ": " << signal.second << std::endl;
    }
}

void MovingAverageCrossover::investment_stratergy() {
    std::cout << "Investment strategy executed. Trading signals:\n";
    displayTradeSignals();
    std::cout << "Current capital: " << get_capital() << std::endl;
}

// ???
bool MovingAverageCrossover::valid_pay_freq(std::string freq) {
    return (freq == "Monthly" || freq == "Quarterly" || freq == "Annually");
}

void MovingAverageCrossover::set_investment_type() {
    this->investment_type = "Moving Average Crossover";
}

double MovingAverageCrossover::MovingAverage(int period) {
    if (prices.size() < period) {
        throw std::out_of_range("Not enough data to calculate moving average.");
    }
    double sum = 0;
    for (size_t i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / period;
}

void MovingAverageCrossover::detectCrossover(){
    largePeriod(Period1, Period2);
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
        if (previousShortMA <= previousLongMA && shortMA > longMA){
            int day = prices.size();
            tradeSignals.emplace_back(day, "Buy");
        }
        // Sell signal (shortMA crosses below longMA)
        else if (previousShortMA >= previousLongMA && shortMA < longMA) {
            int day = prices.size();
            tradeSignals.emplace_back(day, "Sell");
        }
    }

    // Update previous values
    previousShortMA = shortMA;
    previousLongMA = longMA;
}

void MovingAverageCrossover::executeStrategy(){
    // Detect crossover
    detectCrossover();
}