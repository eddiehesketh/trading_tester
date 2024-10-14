// Investment code file, defining the functions outlined in the investment header file
#include "Investment.h" // Including header main fule,

// Informing program, standard namespace will be used.
using namespace std;

// Investment constructor, initialising all protected variables and passing the stock info into the read data class.
Investment::Investment(float initial_capital, string stock_info_):capital(initial_capital), index(0), 
                                                                    final_capital(0), profits(0),widthdrawn_cash(0), period(0), momentum(0), 
                                                                    Period1(0), Period2(0), shortPeriod(0), longPeriod(0), shares(0),
                                                                    ReadData(stock_info_){};

// Default constructor, setting defualt values into the Investment constructor.
Investment::Investment():Investment(0.0, NULL){};


// Getter function to return capital.
float Investment::get_capital(){return this->capital;}

// Setter function to set capital.
void Investment::set_capital(float new_capital){this->capital = new_capital;} 


// Checks if start date is valid.
bool Investment::valid_start_date(string _start_date){

    // For loop iterating over all dates of a given stock historical data, checking to see if the string matches one of those dates.
    for (int i = 0; i < get_dates().size(); i++){

        // Checking if any dates match.
        if (_start_date == get_dates()[i]){

            // If so, set the index so that the program knows where to start investment stratergies from.
            set_index(i);
            set_start_date(_start_date); // Sets the start date.

            // Return true to caller.
            return true;
        }
    }

    // If there are no matches, return false to caller.
    return false;

}

// Setter for pay frequencey.
void Investment::set_pay_freq(string freq){this->pay_freq = freq;}

// Getter for pay frequencey.
string Investment::get_pay_freq(){return this->pay_freq;}

// Setter for data index for where to start investments from.
void Investment::set_index(int _index){this->index = _index;}

// Getter for the start index.
int Investment::get_index(){return this->index;}

// Setter for the final capital.
void Investment::set_final_capital(int _capital){this->final_capital = _capital;}

// Setter for the profits.
void Investment::set_profits(float _profits){this->profits = _profits;}

// Getter for the final capital.
float Investment::get_final_capital(){return this->final_capital;}

// Setter for the start date.
void Investment::set_start_date(string _start_date){this->start_date_ = _start_date;}

// Setter for the reinvestment status.
void Investment::set_reivest_status(bool stat){this->reinvest_status = stat;}

// Setter for the widthdrawn cash.
void Investment::set_widthdrawn_cash(float v){this->widthdrawn_cash = v;}

// Getter for the widthdrawn cash.
float Investment::get_widthdrawn_cash(){return this->widthdrawn_cash;}

// Getter for the investment type.
string Investment::get_investment_type(){return this->investment_type;}

// Getter for the profits.
float Investment::get_profits(){return this->profits;}

// Virtual function for calculating momentum, will be overidden in later sub classes.
double Investment::calc_momentum(int period, int index_val){return 0;}

// Virtual function for detecting momentum, will be overidden in later sub classes.
void Investment::detect_momentum(){};

// Calulates how many shares can be bought with a given capital.
int Investment::capital_to_shares(double capital, double closePrice){
    // Determines if shares can be bought

    // Checks for a valid capital value.
    if (capital <= 0){
        std::cerr << "Error: Insufficient capital to buy shares." << std::endl; // If invalid inform user.
        return 0; // Zero shares can be bought.
    }
    // Returns number of purchasable shares
    return static_cast<int>(capital / closePrice);
}

// Calculates how much capital there is based on the number of shares.
double Investment::shares_to_capital(int shares, double closePrice){
    // Determines if shares can be sold

    // Checks for a valid number of shares.
    if (shares <= 0){
        std::cerr << "Error: Cannot convert negative shares to capital." << std::endl; // Inform user if invalid.
        return 0.0; // Returns 0.
    }
    // Returns number of sellable shares if valid.
    return shares * closePrice;
}

// Virutal finailizes simulation function which will be incorporated in later sub classes.
void Investment::finalize_simulation(){};

// Virtual large period function which will be incorporated in later sub classes.
void Investment::large_period(int period1, int period2){};

// Virtual moving average function which will be incorporated in later sub classes.
double Investment::moving_average(int period, int currentIndex){return 0;}

// Virtual detect crossover function which will be incorporated in later sub classes.
void Investment::detect_crossover(){};

// Function to find the index of a specific start date in the vector of dates.
int Investment::date_index(const std::vector<std::string>& dates, const std::string& _start_date){

    // Iterate over the vector of dates
    for (int i = 0; i < dates.size(); i++){

        // Check if the current date matches the provided start date
        if (dates[i] == _start_date) {
            return i; // Return the index if a match is found
        }
    }
    return -1; // Return -1 if the start date is not found in the vector
}

// Getter function for the reinvestment status.
bool Investment::get_reinvest_status(){return this->reinvest_status;}

// Getter function to return start date.
string Investment::get_start_date(){return this->start_date_;}