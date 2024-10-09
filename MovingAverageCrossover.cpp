#include "MovingAverageCrossover.h"
#include <iostream>

MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod):Investment(initial_capital, stock_info_), shortPeriod(shortPeriod), longPeriod(longPeriod) {
    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

void MovingAverageCrossover::addPrice(double price){
    prices.push_back(price);
    if (prices.size() >= longPeriod) {
        executeStrategy();
    }
}

double MovingAverageCrossover::calculateSMA(int period){
    double sum = 0;
    for (int i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / period;
}

void MovingAverageCrossover::executeStrategy(){
    if (prices.size() < longPeriod) return;

    double shortMA = calculateSMA(shortPeriod);
    double longMA = calculateSMA(longPeriod);
    int day = prices.size();

    static bool inPosition = false;

    // Check for buy signal
    if (shortMA > longMA && !inPosition){
        tradeSignals.emplace_back(day, "Buy");
        inPosition = true;
    }
    // Check for sell signal
    else if (shortMA < longMA && inPosition){
        tradeSignals.emplace_back(day, "Sell");
        inPosition = false;
    }
}

void MovingAverageCrossover::displayTradeSignals(){
    for (const auto& signal : tradeSignals) {
        std::cout << "Day " << signal.first << ": " << signal.second << std::endl;
    }
}

void MovingAverageCrossover::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    displayTradeSignals();
    std::cout << "Current capital: " << get_capital() << std::endl;
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){
    return (freq == "Monthly" || freq == "Quarterly" || freq == "Annually");
}

void MovingAverageCrossover::set_investment_type(){
    std::string investmentType = "Mean Reversion";
}

int MovingAverageCrossover::MovingAverage10D(){
    if (prices.size() < 10) {
        throw std::out_of_range("Not enough data to calculate 10-day moving average.");
    }
    // Sum the last 20 prices
    double sum = 0;
    for (size_t i = prices.size() - 10; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / 10.0;
}

int MovingAverageCrossover::MovingAverage20D(){
    if (prices.size() < 20) {
        throw std::out_of_range("Not enough data to calculate 20-day moving average.");
    }
    // Sum the last 20 prices
    double sum = 0;
    for (size_t i = prices.size() - 20; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / 20.0;
}