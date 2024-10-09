#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod)
    : Investment(initial_capital, stock_info_) {
    this->shortPeriod = shortPeriod;
    this->longPeriod = longPeriod;
    if (valid_start_date(_start_date)) {
        investment_stratergy();
    }
}

void MovingAverageCrossover::addPrice(double price) {
    prices.push_back(price);
    if (prices.size() >= longPeriod) {
        executeStrategy();
    }
}

void MovingAverageCrossover::executeStrategy() {
    if (prices.size() < longPeriod) return;

    // Calculate moving averages
    double MA1 = MovingAverage(shortPeriod);
    double MA2 = MovingAverage(longPeriod);
    
    // Detect crossover
    detectCrossover(); // This will handle buying/selling based on crossover
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
    if (prices.size() < longPeriod) return;

    double MA1 = MovingAverage(shortPeriod); // Calculate 10-day SMA
    double MA2 = MovingAverage(longPeriod);   // Calculate 20-day SMA
    static double previousMA1 = 0.0; // Store previous 10-day SMA
    static double previousMA2 = 0.0;  // Store previous 20-day SMA

    // Check for crossover
    if (previousMA1 != 0.0 && previousMA2 != 0.0) {
        // Buy signal (shortMA crosses above longMA)
        if (previousMA1 <= previousMA2 && MA1 > MA2){
            int day = prices.size(); // Current day index
            tradeSignals.emplace_back(day, "Buy");
        }
        // Sell signal (shortMA crosses below longMA)
        else if (previousMA1 >= previousMA2 && MA1 < MA2) {
            int day = prices.size(); // Current day index
            tradeSignals.emplace_back(day, "Sell");
        }
    }

    // Update previous values
    previousMA1 = MA1;
    previousMA2 = MA2;
}