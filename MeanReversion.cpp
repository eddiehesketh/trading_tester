#include "MeanReversion.h"
#include <iostream>
#include <numeric>

MeanReversion::MeanReversion(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info), meanPeriod(period){
    if (valid_start_date(_start_date)){
        investment_stratergy();
    }
}

void MeanReversion::addPrice(double price){
    signals.push_back(price);
    if (signals.size() > meanPeriod) {
        signals.erase(signals.begin());
    }
}

void MeanReversion::investment_stratergy(){
    if (signals.size() < meanPeriod) {
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

void MeanReversion::displayTradeSignals(){
    std::cout << "Trade signals based on mean reversion strategy:\n";
    for (size_t i = 0; i < signals.size(); ++i) {
        std::cout << "Price: " << signals[i] << "\n";
    }
}

bool MeanReversion::valid_pay_freq(std::string freq){
    return (freq == "monthly" || freq == "quarterly" || freq == "annually");
}

void MeanReversion::set_investment_type(){
    std::string investmentType = "Mean Reversion";
}