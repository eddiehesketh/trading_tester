#include "ReadData.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    ReadData* stock1 = new ReadData("test_csvfile.csv");

    for (size_t i = 0; i < stock1->get_close_prices().size(); i++) {
        cout << "Date: " << stock1->get_dates()[i] << ", Open: $" << stock1->get_open_prices()[i] <<", Close: $" << stock1->get_close_prices()[i] << ", Volume: $" << stock1->get_volume()[i] <<", High: $" << stock1->get_stock_high()[i] <<", Low: $" << stock1->get_stock_low()[i] << endl;
    }

    delete stock1;

    cout << "\n\n\n\n";

    ReadData* stock2 = new ReadData("test_csv_2.csv");

    for (size_t i = 0; i < stock2->get_close_prices().size(); i++) {
        cout << "Date: " << stock2->get_dates()[i] << ", Open: $" << stock2->get_open_prices()[i] <<", Close: $" << stock2->get_close_prices()[i] << ", Volume: $" << stock2->get_volume()[i] <<", High: $" << stock2->get_stock_high()[i] <<", Low: $" << stock2->get_stock_low()[i] << endl;
    }

    delete stock2;





    // for (size_t i = 0; i < stock1->get_dates().size(); i++) {
    //     cout << "Date: " << stock1->get_dates()[i] << ", Open: " << stock1->get_open_prices()[i] << endl;
    // }



    return 0;
}