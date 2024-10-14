#include "Momentum.h"
#include "ReadData.h"
#include "Investment.h"

// FOR MOMENTUM
int main(){
    std::string csvFileName = "MA.csv";
    Momentum momentem("31/1/2000", 10000.0, csvFileName, 10);
    return 0;
}