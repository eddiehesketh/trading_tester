#include "Momentum.h"
#include <iostream>
#include <numeric>

Momentum::Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info){
    this->Period = period;

    set_investment_type(); 
    investment_stratergy();
    // if (valid_start_date(_start_date)){
    //     investment_stratergy();
    // }
}

bool Momentum::valid_pay_freq(std::string freq){
    return true;
}

double Momentum::MovingAverage(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0;

    // Calculate the sum of the prices for the moving average
    for (int i = index_val; i >= (index_val - period + 1); i--){
        sum += close_stock[i]; // Use closePrices instead of prices
    }

    return sum / period; // Return the calculated moving average
}

void Momentum::investment_stratergy(){
    if (signals.size() < meanPeriod){
        std::cout << "Not enough data to determine mean.\n";
        return;
    }

    // Calculate the mean price
    double sum = std::accumulate(signals.begin(), signals.end(), 0.0);
    meanPrice = sum / meanPeriod;

    // Last price for comparison
    double lastPrice = signals.back();

    // Simple mean reversion logic
    if (lastPrice < meanPrice) {
        std::cout << "Buy signal generated: Current Price (" << lastPrice << ") is below Mean Price (" << meanPrice << ").\n";
        // Here, you could implement logic to buy the asset, increase capital, etc.
    } else if (lastPrice > meanPrice) {
        std::cout << "Sell signal generated: Current Price (" << lastPrice << ") is above Mean Price (" << meanPrice << ").\n";
        // Here, you could implement logic to sell the asset, decrease capital, etc.
    } else {
        std::cout << "No action: Current Price (" << lastPrice << ") is equal to Mean Price (" << meanPrice << ").\n";
    }
}

void Momentum::displayTradeSignals(){
    std::cout << "Trade signals based on mean reversion strategy:\n";
    for (size_t i = 0; i < signals.size(); ++i){
        std::cout << "Price: " << signals[i] << "\n";
    }
}

bool Momentum::valid_pay_freq(std::string freq){
    return (freq == "monthly" || freq == "quarterly" || freq == "annually");
}

void Momentum::set_investment_type(){
    this-> investment_type = "Momentum";
}