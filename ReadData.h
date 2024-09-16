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

        vector<string> date;
        vector<string> stock_open;
        vector<string> stock_close;
        vector<string> stock_high;
        vector<string> stock_low;
        vector<string> volume;  


    public:

        ReadData();

        string clean_value();

        






    
};



#endif
