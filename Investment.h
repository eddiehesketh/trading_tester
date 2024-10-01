#ifndef INVESTMENT_H
#define INVESTMENT_H
#include "ReadData.h"


class Investment: public ReadData{

    protected:
        float capital;
        float invest_return;
        float deposit_amount;
        int index;
        float final_capital;
        float profits;
        std::string start_date_;

    public:

        Investment(float initial_capital, std::string stock_info_);

        // Investment();

        virtual void investment_stratergy() = 0;



        virtual float get_capital();

        virtual void set_capital(float new_capital);

        virtual bool valid_start_date(std::string _start_date);

        virtual void set_index(int _index);

        virtual void set_final_capital(int _capital);

        virtual float get_final_capital();

        virtual void set_profits(float _profits);

        virtual void set_start_date(std::string _start_date);

        virtual int get_index();
 


};









#endif






