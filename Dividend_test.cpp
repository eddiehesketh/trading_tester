#include "ReadData.h"
#include "Dividend.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    Dividend s1("2/1/2020", 1000, "Quarterly", "microsoft.csv", false);

     cout << "hello" << endl;
    cout << "initial capital: $" << s1.get_capital() << endl;
    cout << "Final capital: $" << s1.get_final_capital() << endl;
    cout << "Final Profits: $" << s1.get_profits() << endl;



    return 0;
}