#ifndef DIVIDEND_H
#define DIVIDEND_H
#include "ReadData.h"
#include "Investment.h"


class Dividend: public Investment{

    protected:
        float dividend_yield;
        float widthdrawn_cash;
        std::string pay_freq;
        bool reinvest_status;


    public:

        Dividend(std::string start_date_, float initial_capital, std::string pay_freq_, std::string stock_info, bool status);

        void investment_stratergy() override;

        bool valid_pay_freq(std::string freq) override;

        bool valid_start_date(std:: string start) override;




};




#endif
