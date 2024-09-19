#ifndef SETDEPOSIT_H
#define SETDEPOSIT_H
#include "ReadData.h"


class SetDeposit: public ReadData{

    protected:
        float invest_return;
        float deposit_amount;
        int index;
        std::string start_date;
        

    public:
        SetDeposit(std::string _start_date, std::string stock_info);

        bool start_date(std::string _start_date);

        void set_index(int _index);

        void invest_strat() override;



};








#endif