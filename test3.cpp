#include <iostream>
#include "MeanReversion.h"
#include "MovingAverage.h"
#include "ReadData.h"
#include <string>

// // FOR MEAN REVERSION
// int main() {
//     std::string csvFileName = "test_csvfile.csv"; 
//     float initialCapital = 10000.0f; 
//     std::string stockInfo = "Example Stock";
//     int meanPeriod = 5;
//     std::string startDate = "2023-01-01"; 
//     MeanReversion meanReversion(startDate, initialCapital, stockInfo, meanPeriod);
//     ReadData readData(csvFileName);
//     std::vector<float>& closePrices = readData.get_close_prices();
//     std::cout << "Testing Mean Reversion Strategy:\n";
//     for (double price : closePrices) {
//         meanReversion.addPrice(price);
//     }
//     meanReversion.investment_stratergy();
//     meanReversion.displayTradeSignals();
//     return 0;
// }

// FOR MOVING AVERAGE
int main() {
    std::string csvFileName = "test_csvfile.csv";
    float initialCapital = 10000.0f;
    std::string stockInfo = "Example Stock"; 
    int shortPeriod = 5; 
    int longPeriod = 10; 
    std::string startDate = "2023-01-01";
    MovingAverage movingAverage(startDate, initialCapital, stockInfo, shortPeriod, longPeriod);
    ReadData readData(csvFileName);
    const std::vector<float>& closePrices = readData.get_close_prices();
    std::cout << "Testing Moving Average Strategy:\n";
    for (double price : closePrices) {
        movingAverage.addPrice(price);
    }
    movingAverage.investment_stratergy();
    return 0;
}
