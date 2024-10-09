#include <iostream>
#include "MeanReversion.h"
#include "MovingAverageCrossover.h"
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

// FOR MOVING AVERAGE CROSSOVER
int main() {
    std::string csvFileName = "apple.csv"; // Ensure this file exists
    float initialCapital = 10000.0f;
    std::string stockInfo = "Example Stock"; 
    int shortPeriod = 5; 
    int longPeriod = 10; 
    std::string startDate = "2023-01-01";
    // Create an instance of MovingAverageCrossover
    MovingAverageCrossover movingAverage(startDate, initialCapital, stockInfo, shortPeriod, longPeriod);
    
    // Create ReadData instance to read stock prices
    ReadData readData(csvFileName);
    
    // Get the closing prices
    const std::vector<float>& closePrices = readData.get_close_prices();
    
    std::cout << "Testing Moving Average Strategy:\n";
    for (double price : closePrices) {
        movingAverage.addPrice(price); // Add each price to the MovingAverageCrossover instance
    }
    
    movingAverage.investment_stratergy(); // Execute investment strategy

    // Output the closing prices
    for (size_t i = 0; i < closePrices.size(); ++i) {
        std::cout << "Close Price on " << readData.get_dates()[i] << ": " << closePrices[i] << std::endl;
    }

    try {
        double ma20 = movingAverage.MovingAverage20D();
        std::cout << "The previous 20-day moving average is: " << ma20 << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Handle the case where there are not enough prices
    }

    try {
        double ma10 = movingAverage.MovingAverage10D();
        std::cout << "The previous 10-day moving average is: " << ma10 << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl; // Handle the case where there are not enough prices
    }

    return 0;
}
