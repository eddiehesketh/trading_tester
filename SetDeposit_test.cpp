#include "ReadData.h"
#include "SetDeposit.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    SetDeposit s1("10/5/2023", "test_csv_2.csv", 500);

    cout << "initial capital: $" << s1.get_capital() << endl;
    cout << "Final capital: $" << s1.get_final_capital() << endl;



    return 0;
}