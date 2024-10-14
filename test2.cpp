#include "MovingAverageCrossover.h"
#include "ReadData.h"
#include "Investment.h"

// FOR MOVING AVERAGE CROSSOVER
int main(){
    std::string csvFileName = "MA.csv";
    MovingAverageCrossover movingAverage("31/1/2000", 10000.0, csvFileName, 10, 20);
    return 0;
}