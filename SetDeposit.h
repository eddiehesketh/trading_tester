#ifndef SETDEPOSIT_H
#define SETDEPOSIT_H
#include "ReadData.h"
#include "Investment.h"


class SetDeposit: public Investment{

    public:
        SetDeposit(std::string _start_date, std::string stock_info, int capital);

        void investment_stratergy() override;

        bool valid_pay_freq(std::string freq) override;


};

#endif