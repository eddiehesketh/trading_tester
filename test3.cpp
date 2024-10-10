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
    std::string csvFileName = "MA.csv"; // Ensure this file exists
    float initialCapital = 10000.0f;
    std::string stockInfo = "Example Stock"; 
    int Period1 = 10; 
    int Period2 = 20; 
    std::string startDate = "2000-01-01";

    // Create an instance of MovingAverageCrossover
    MovingAverageCrossover movingAverage(startDate, initialCapital, stockInfo, Period1, Period2);
    
    // Create ReadData instance to read stock prices
    ReadData readData(csvFileName);
    
    // Get the closing prices
    const std::vector<float>& closePrices = readData.get_close_prices();

    for (double price : closePrices) {
        movingAverage.addPrice(price);
    }

    movingAverage.investment_stratergy(); // Execute investment strategy

    // const std::vector<std::string>& dates = readData.get_dates();
    // for (size_t i = 0; i < dates.size(); ++i) {
    //     std::cout << "Date " << i + 1 << ": " << dates[i] << std::endl; // Print the date
    // }

    return 0; // Ensure you return an integer from main


    // // Moving average calc
    // for (size_t i = 0; i < closePrices.size(); ++i) {
    //     double price = closePrices[i];
    //     movingAverage.addPrice(price); 

    //     // Check if there are enough prices for short-term moving average
    //     if (i + 1 >= shortPeriod){
    //         double MA1 = movingAverage.MovingAverage(shortPeriod);
    //         std::cout << "The previous " << shortPeriod << " day moving average is: " << MA1 << std::endl;
    //     }
    //     // Check if there are enough prices for long-term moving average
    //     if (i + 1 >= longPeriod){
    //         double MA2 = movingAverage.MovingAverage(longPeriod);
    //         std::cout << "The previous " << longPeriod << " day moving average is: " << MA2 << std::endl;
    //     }
    // }
    


    // // Output the closing prices
    // for (size_t i = 0; i < closePrices.size(); ++i) {
    //     std::cout << "Close Price on " << readData.get_dates()[i] << ": " << closePrices[i] << std::endl;
    // }

    // for (size_t i = 0; i < closePrices.size(); ++i) {
    //     std::cout << closePrices[i] << std::endl;
    // }
}
