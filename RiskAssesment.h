// Risk assesment class provides a risk rating based on the type of investment.

// Defining the class and including the relevant investment header file.
#ifndef RISKASSESMENT_H
#define RISKASSESMENT_H
#include "Investment.h"
#include "MovingAverageCrossover.h"
#include "SetDeposit.h"
#include "Momentum.h"
#include "Dividend.h"
#include "ReadData.h"


// Risk assesment class.
class RiskAssesment{

    protected:

        // Risk status variable.
        std::string risk_rating;

    public:

        // Risk assesment constructor, taking in an investment pointer.
        RiskAssesment(Investment* stock);

        // Risk assesment function which will determine the risk of an investment.
        void risk_assesment(Investment* p);

        // Setter for the risk rating.
        void set_risk_rating(std::string rating);

        // Getter for the risk rating.
        std::string get_risk_rating();

};


#endif