// Portfolio class is used to build a collection of investment stratergies.

// Defining the portfolio class and including investment header file.
#ifndef PORTFOLIO_H
#define  PORTFOLIO_H
#include "Investment.h"

// Portfolio class.
class Portfolio{

    protected:

        // Double investment pointer, which will point to an array of investment pointers.
        Investment** investments;

        // Value made up of the sum of all investment capital.
        float portfolio_value;

        // Capacity of investments.
        int capacity;

        // Count of investments.
        int count;

    
    public:

        // Defualt portfolio constructor.
        Portfolio();

        // Add investment function.
        void add_investment(Investment* _invesment);

        // Remove investment function.
        void remove_investment(int index);

        // Setter to set the portfolio value.
        void set_portfolio_value();


        // Getter to get portfolio value.
        float get_portfolio_value();

        // Setter to set the count variable.
        void set_count(int c);

        // Getter to return the count variable.
        int get_count();

        // Write portfolio function to write a file.
        void write_portfolio_summary();

        // Destructor.
        ~Portfolio();


};






#endif