#ifndef INVESTMENT_H
#define INVESTMENT_H
#include "ReadData.h"


class Investment{

    protected:
        float capital;

    public:

        Investment(float initial_capital);

        Investment();

        virtual void investment_stratergy(std::vector<float> open_prices, std::vector<float> close_prices) = 0;



        float get_capital();

        void set_capital(float new_capital);


};







#endif