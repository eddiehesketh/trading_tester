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

    Dividend s1("28/10/2005", 500, "Monthly", "test_csv_2.csv", true);

     cout << "hello" << endl;
    cout << "initial capital: $" << s1.get_capital() << endl;
    cout << "Final capital: $" << s1.get_final_capital() << endl;



    return 0;
}