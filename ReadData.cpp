#include "ReadData.h"
#include <iostream>

using namespace std;

ReadData::ReadData(int _index): index(_index){};
ReadData::ReadData(): ReadData(0){};


void ReadData::addElement(int price){open_prices.push_back(price);}

void ReadData::readOpenPrices(string filename){
    ifstream file(filename);
    
}
