// Dividend class inherits from the investment class and simulates dividend investment plans.

// Defining the dividend class and including the relevant libraries, including the read data class and the investment class.
#ifndef DIVIDEND_H
#define DIVIDEND_H
#include "ReadData.h"
#include "Investment.h"

// Dividend class publicly inheriting from investment.
class Dividend: public Investment{


    public:

        // Dividend constructor, taking in a start date, inital capital, pay frequencey, stock information and reinvestment status.
        Dividend(std::string start_date_, float initial_capital, std::string pay_freq_, std::string stock_info, bool status);
        Dividend();

        // Overriding the investment stratergy function, for re-implementation.
        void investment_stratergy() override;

        // Overriding the valid pay frequencey function, for re-implementation.
        bool valid_pay_freq(std::string freq) override;

        // Overriding the valid start date function, for re-implementation.
        bool valid_start_date(std:: string start) override;

        // Overriding the set investment type function, for re-implementation.
        void set_investment_type() override;

};

#endif
