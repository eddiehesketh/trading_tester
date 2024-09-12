#ifndef READDATA_H
#define READDATA_H
using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>




class ReadData{

    protected:
        vector<int> open_prices = {};
        int index;


    public:

    ReadData();
    ReadData(int _index);

    void addElement(int price);

    void readOpenPrices(string filename);

    







};



#endif
