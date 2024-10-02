#ifndef DISPLAY_H
#define DISPLAY_H
#include "ReadData.h"

class Display: public ReadData{

    public:

        Display(std::string stock);

        // std::string day_one_open();
        std::string single_open_prices(int day);
        std::string single_close_prices(int day);
        std::string single_dates(int day);
        std::string single_volumes(int day);




};

#endif