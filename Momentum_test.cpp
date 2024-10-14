#include "ReadData.h"
#include "Momentum.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){
    Momentum s1("2/1/2020", 1000, "tesla.csv", 15);
    cout << "initial capital: $" << s1.get_capital() << endl;
    cout << "Final capital: $" << s1.get_final_capital() << endl;
    return 0;
}