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
    float initialCapital = 10000.0f;
    std::string stockInfo = csvFileName; 
    int Period1 = 10; 
    int Period2 = 20; 
    std::string startDate = "2001-01-01";

    // Create an instance of MovingAverageCrossover
    MovingAverageCrossover movingAverage(startDate, initialCapital, stockInfo, Period1, Period2);
    
    // Load prices from CSV directly in MovingAverageCrossover
    movingAverage.investment_stratergy();
    
    return 0;
}