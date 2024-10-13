#include <iostream>
#include "Momentum.h"
#include "MovingAverageCrossover.h"
#include "ReadData.h"
#include "Investment.h"
#include <string>

// // FOR MOMENTUM
// int main() {
//     std::string csvFileName = "test_csv_2.csv";
//     Momentum momentem("3/1/2000", 10000.0, csvFileName, 10);
//     return 0;
// }

// FOR MOVING AVERAGE CROSSOVER
int main() {
    std::string csvFileName = "MA.csv";
    MovingAverageCrossover movingAverage("3/5/2000", 10000.0, csvFileName, 10, 20);
    return 0;
}