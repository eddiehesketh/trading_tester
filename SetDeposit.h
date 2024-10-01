#ifndef SETDEPOSIT_H
#define SETDEPOSIT_H
#include "ReadData.h"
#include "Investment.h"


class SetDeposit: public Investment{

    protected:
        float deposit_amount;
        

    public:
        SetDeposit(std::string _start_date, std::string stock_info, int capital);

        void investment_stratergy() override;


};








#endif