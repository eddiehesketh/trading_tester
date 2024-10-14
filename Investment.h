// The investment class is a pure abstract class, publicly inheriting from ReadData class, serving as a base class for different investment stratergies.

// Defining the class.
#ifndef INVESTMENT_H
#define INVESTMENT_H
#include "ReadData.h" // Including the read data header file, to allow for inheritance.

// Investment class acting as a pure abstract class
class Investment: public ReadData{

    protected: // protected data types.

        // Basic investment paramters.
        float capital; // Initial investment capital
        int index; // // Index to track the start date in the dates vector from read data.
        float final_capital;  // Capital after applying investment strategies.
        float profits;  // Profits from the investment.
        std::string start_date_; // Start date of the investment.
        std::string investment_type; // Type of investment.

        // Cash withdrawal and frequency-related members.
        float widthdrawn_cash; // Amount of cash withdrawn from the investment
        std::string pay_freq; // Payment frequency.
        bool reinvest_status; // Whether frequent returns are reinvested into the market.

        // Variables for momentum based strategy. 
        int period; // Period for momentum calculation.
        int momentum; // Momentum value.

        // Variables for Moving Average Crossover strategy.
        int Period1; // First period for the moving average crossover.
        int Period2; // Second period for the moving average crossover.
        int shortPeriod; // Shorter of the two periods.
        int longPeriod;  // Longer of the two periods

        // Shares between Momentum and Moving Average Crossover
        float moving_capital;
        int shares; // Number of shares owned.
        bool isInvested;  // Flag to check if the investment is active.

    public:

        // Investment class contructor, which takes in an inital capital value and stock file title.
        Investment(float initial_capital, std::string stock_info_);
        Investment(); // Default constructor.

        // Virtual destructor.
        virtual ~Investment() = default;

        // Pure virtual function for the investment stratergy.
        virtual void investment_stratergy() = 0;

        // Getter function to return the inital captial.
        float get_capital();

        // Setter function to set the capital.
        void set_capital(float new_capital);

        // Virtual function checking if a given start date is valid.
        virtual bool valid_start_date(std::string _start_date);

        // Setter function to set the index.
        void set_index(int _index);

        // Setter function to set the final capital.
        void set_final_capital(int _capital);

        // Getter function to return the final capital.
        float get_final_capital();

        // Setter function to set the final profits.
        void set_profits(float _profits);

        // Setter function to set the start date.
        void set_start_date(std::string _start_date);

        // getter function to return the date index.
        int get_index();

        // Virtual function to check the inputted pay frequencey is valid.
        virtual bool valid_pay_freq(std::string freq) = 0;

        // Setter function to set the reinvestment status.
        void set_reivest_status(bool stat);

        // Setter function to set the pay frequency.
        void set_pay_freq(std::string freq);

        // Getter function to return the pay frequencey.
        std::string get_pay_freq();

        // Setter function to set the widthdrawn cash protected variable.
        void set_widthdrawn_cash(float v);

        // Getter function to return the widthdrawn cash.
        float get_widthdrawn_cash();

        // Getter function to return the profits.
        float get_profits();

        // Pure virtual function used to set the investment type.
        virtual void set_investment_type() = 0;

        // Getter function to return the investment type.
        std::string get_investment_type();

        // Virtual calculate momentum function.
        virtual double calc_momentum(int period, int index_val);
        
        // Virtual detect momentum function.
        virtual void detect_momentum();

        // Capital to shares function to calulate the number of shares based off a certain capital.
        int capital_to_shares(double capital, double closePrice);

        // Shares to capital function to determine the captial based off a set number of shares.
        double shares_to_capital(int shares, double closePrice);

        // Virtual finalise simulation function used to simulate high frequency stratergies.
        virtual void finalise_simulation(); 

        // Virtual function used to determine the large period.
        virtual void large_period(int period1, int period2);
        
        // Virtual function used to determine the moving average combintion.
        virtual double moving_average(int period, int currentIndex);

        // Virtual function which detects crossovers of different moving averages.
        virtual void detect_crossover();

        // Virtual function used to determine the index of a given date
        virtual int date_index(const std::vector<std::string>& dates, const std::string& _start_date);

        // getter function to return the reinvestment status.
        bool get_reinvest_status();       

        // Getter function to return the start date.
        std::string get_start_date(); 
};

#endif

