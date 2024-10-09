#ifndef PORTFOLIO_H
#define  PORTFOLIO_H
#include "Investment.h"

class Portfolio{

    protected:
        Investment** investments;
        float portfolio_value;
        int capacity;
        int count;

    
    public:

        Portfolio();

        void add_investment(Investment* _invesment);

        void remove_investment(int index);

        // void set_portfolio_value();

        void set_portfolio_value();


        float get_portfolio_value();

        void set_count(int c);

        int get_count();

        ~Portfolio();






};






#endif