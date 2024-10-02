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

    string today_price = d1.single_open_prices(1);
    string today_close = d1.single_close_prices(1);
    string date1 = d1.single_dates(1);
    string vol1 = d1.single_volumes(1);
    string five_day_open = d1.single_open_prices(5);
    string five_day_close = d1.single_close_prices(5);
    string date2 = d1.single_dates(5);
    string vol2 = d1.single_volumes(5);

    cout << "Open " << today_price << ", Close " << today_close << ", Date "<< date1 << ", Volume " << vol1 <<  endl;
    cout << "Open " << five_day_open << ", Close " << five_day_close << ", Date "<< date2 << ", Volume " << vol2 <<  endl;





    return 0;
}