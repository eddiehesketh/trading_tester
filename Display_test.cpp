#include "ReadData.h"
#include "Display.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    Display d1("test_csv_2.csv");



    for (int i = 1; i < 8; i++){
        cout << "Open " << d1.single_open_prices(i) << ", Close " << d1.single_close_prices(i) << ", Date "<< d1.single_dates(i) << ", Volume " << d1.single_volumes(i) << ", Change " << d1.daily_change(i) << endl;


    }


    return 0;
}