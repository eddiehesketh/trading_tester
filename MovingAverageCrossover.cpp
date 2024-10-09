#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod):Investment(initial_capital, stock_info_){
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

double MovingAverageCrossover::calculateSMA(int period) {
    double sum = 0;
    for (int i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / period;
}

void MovingAverageCrossover::executeStrategy() {
    if (prices.size() < longPeriod) return;

    double shortMA = calculateSMA(shortPeriod);
    double longMA = calculateSMA(longPeriod);
    int day = prices.size();

    static bool inPosition = false;

    // Check for buy signal
    if (shortMA > longMA && !inPosition) {
        tradeSignals.emplace_back(day, "Buy");
        inPosition = true;
    }
    // Check for sell signal
    else if (shortMA < longMA && inPosition) {
        tradeSignals.emplace_back(day, "Sell");
        inPosition = false;
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

bool MovingAverageCrossover::valid_pay_freq(std::string freq) {
    return (freq == "Monthly" || freq == "Quarterly" || freq == "Annually");
}

void MovingAverageCrossover::set_investment_type() {
    std::string investmentType = "Moving Average Crossover"; // Updated to correct strategy name
}

double MovingAverageCrossover::MovingAverage(int period) {
    if (prices.size() < period) {
        throw std::out_of_range("Not enough data to calculate moving average.");
    }
    
    double sum = 0;
    for (size_t i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / period; // Return the average
}

double MovingAverageCrossover::MovingAverage10D() {
    return MovingAverage(10); // Use the generalized function for 10 days
}

double MovingAverageCrossover::MovingAverage20D() {
    return MovingAverage(20); // Use the generalized function for 20 days
}