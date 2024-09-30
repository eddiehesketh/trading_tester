#ifndef SETDEPOSIT_H
#define SETDEPOSIT_H
#include "ReadData.h"
#include "Investment.h"


class SetDeposit: public ReadData, Investment{

    protected:
        float invest_return;
        float deposit_amount;
        int index;
        float final_capital;
        float profits;
        std::string start_date;
        

    public:
        SetDeposit(std::string _start_date, std::string stock_info, int capital);

        void investment_stratergy() override;

        bool start_date(std::string _start_date);

        void set_index(int _index);

        void set_final_capital(int _capital);

        void set_profits(float _profits);

        

        // void invest_strat() override;

        int get_index();



};








#endif