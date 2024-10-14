// Including relevant header files.
#include "RiskAssesment.h"
#include "Investment.h"

// Using the standard namespace.
using namespace std;

// Constructor.
RiskAssesment::RiskAssesment(Investment* stock){

    // Calling risk assesment function based on the investment pointer.
    risk_assesment(stock);

}

// Risk assesment function determines the risk based on the investment type.
void RiskAssesment::risk_assesment(Investment* stock){

    // Determine the investment type based on the investment pointer.
    string investment_type = stock->get_investment_type();

    // Compare the investment type to the avaliable options, and assign a corresponding risk rating.
    if (investment_type == "Deposit"){

        // Set deposit to a low to medium risk.
        set_risk_rating("Low to medium");
    } else if (investment_type == "Dividend"){

        // Set dividend to a low risk.
        set_risk_rating("Low");
    } else if (investment_type == "Moving Average Crossover"){

        // Set moving average crossover to a high risk rating.
        set_risk_rating("High");
    } else if (investment_type == "Momentum"){

        // Set momentum to a high risk rating.
        set_risk_rating("High");
    }

}

// Getter for the risk rating.
string RiskAssesment::get_risk_rating(){return this->risk_rating;}


// Setter for the risk rating.
void RiskAssesment::set_risk_rating(string rating){this->risk_rating = rating;}