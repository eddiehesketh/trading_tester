#include "ReadData.h"
#include "MovingAverageCrossover.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int main(){
    MovingAverageCrossover s1("2/1/2020", 5000, "tesla.csv", 5, 20);
    std::cout << "initial capital: $" << s1.get_capital() << std::endl;
    std::cout << "Final capital: $" << s1.get_final_capital() << std::endl;
    return 0;
}