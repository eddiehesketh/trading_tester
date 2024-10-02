#include "ReadData.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){

    ReadData* stock1 = new ReadData("test_csvfile.csv");

    // for (size_t i = 0; i < stock1->get_dates().size(); i++) {
    //     cout << "Date: " << stock1->get_dates()[i] << ", Open: " << stock1->get_open_prices()[i] << endl;
    // }

    return 0;
}