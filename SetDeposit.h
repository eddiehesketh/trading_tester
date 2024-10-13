// Set deposit class inherits from investment, providing 3 layers of inheritance. It runs on the basis of a deposit investment stratergy, determining profits based on a once off buy.

// Defining the class, and including the relevnat header files in the Investment class and ReadData class.
#ifndef SETDEPOSIT_H
#define SETDEPOSIT_H
#include "ReadData.h" 
#include "Investment.h"

// Set Deposit publicly inheriting from investment.
class SetDeposit: public Investment{

    public:

        // Set Deposit constructor, taking in a start date, stock name and an inital amount of capital.
        SetDeposit(std::string _start_date, std::string stock_info, int capital);
        SetDeposit(); // Defualt constructor.

        // Overriding the pure investment stratergy class, ready for implementation.
        void investment_stratergy() override;

        // Overriding the valid pay frequencey class, ready for implementation.
        bool valid_pay_freq(std::string freq) override;

        // Overriding the set investment type class.
        void set_investment_type() override;

};

#endif