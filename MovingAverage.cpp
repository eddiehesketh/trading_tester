#include "MovingAverage.h"
#include <iostream>

MovingAverage::MovingAverage(std::string _start_date, float initial_capital, std::string stock_info_, int shortPeriod, int longPeriod):Investment(initial_capital, stock_info_), shortPeriod(shortPeriod), longPeriod(longPeriod) {
    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

void MovingAverage::addPrice(double price){
    prices.push_back(price);
    if (prices.size() >= longPeriod) {
        executeStrategy();
    }
}

double MovingAverage::calculateSMA(int period){
    double sum = 0;
    for (int i = prices.size() - period; i < prices.size(); ++i) {
        sum += prices[i];
    }
    return sum / period;
}

void MovingAverage::executeStrategy(){
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

void MovingAverage::displayTradeSignals(){
    for (const auto& signal : tradeSignals) {
        std::cout << "Day " << signal.first << ": " << signal.second << std::endl;
    }
}

void MovingAverage::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    displayTradeSignals();
    std::cout << "Current capital: " << get_capital() << std::endl;
}

bool MovingAverage::valid_pay_freq(std::string freq){
    return (freq == "Monthly" || freq == "Quarterly" || freq == "Annually");
}