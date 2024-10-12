#include <iostream>
#include "MeanReversion.h"
#include "MovingAverageCrossover.h"
#include "ReadData.h"
#include "Investment.h"
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
//     const std::vector<float>& closePrices = readData.get_close_prices();
//     std::cout << "Testing Mean Reversion Strategy:\n";
//     for (double price : closePrices) {
//         meanReversion.addPrice(price);
//     }
//     meanReversion.investment_stratergy();
//     meanReversion.displayTradeSignals();
//     return 0;
// }

// FOR MOVING AVERAGE CROSSOVER
int main() {
    std::string csvFileName = "MA.csv";
    MovingAverageCrossover movingAverage("3/1/2000", 10000.0, csvFileName, 10, 20);
    return 0;

}