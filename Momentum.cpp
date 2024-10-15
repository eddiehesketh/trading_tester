#include "Momentum.h"
#include <iostream>
#include <vector>
#include <string>

// Moving average crossover constuctor, taking in a start data, stock info, and capital amount.
Momentum::Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info){

    // Setting the investment type from the constructor.
    set_investment_type();

    // Setting the pay frequency to once off.
    set_pay_freq("Once off");

    // Initializing the moving average periods and other member variables.
    this->period = period; // Set the period for momentum calculation
    this-> start_date_ = _start_date; // Starting date for the investment strategy
    this->moving_capital = capital; // Initial capital for investment
    shares = 0; // No shares initially owned

    // Check if the provided start date is valid.
    if (valid_start_date(start_date_)){

        // If valid, execute the investment strategy.
        investment_stratergy();
    } else{

        // If not valid, display an error message.
        std::cout << "Non-existant start date" << std::endl;
    }
}

bool Momentum::valid_pay_freq(std::string freq){

    // Checks if the frequencey is once off.
    if (freq == "Once off"){

        // If so return true.
        return true; 
    }
    
    // If not return false.
    return false;
}

void Momentum::set_investment_type(){

    // Sets the investment type to "Momentum".
    this->investment_type = "Momentum";
}

double Momentum::calc_momentum(int period, int index_val){

    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0; 
    
    // If the index is less than the period, return a invalid calculation.
    if (index_val < period - 1){
        return 1000000;
    }

    // Calculate the momentum as the difference between the current price and the price 'period' days ago.
    sum = close_stock[index_val] - close_stock[index_val - period + 1];
    return sum; // Return the calculated momentum value.
}

void Momentum::detect_momentum(){

    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();
    
    // Initialize investment status and index for date lookup.
    isInvested = false; // Track if currently invested
    int index_val = date_index(dates, start_date_); // Get index of the start date

    // Check if the start date is found in the dates vector.
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{

        // Iterate through the close prices starting from the index of the start date.
        for (; index_val < close_stock.size(); index_val++){

            // Calculate the current moving averages for the current index
            double momentum = calc_momentum(period, index_val);

            // Display error if invalid momentum calculation
            if (momentum == 1000000){
            std::cout << "Invalid start date" << std::endl; 
            break;
            }

            // Check for buy signal: Momentum is non-negative and not already invested.
            if (!isInvested && (momentum >= 0)){
                std::cout << "Buy signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
                isInvested = true; // Update investment status to true

                // Check how many shares can be purchased with the available capital.
                int sharesToBuy = capital_to_shares(moving_capital, close_stock[index_val]);
                if (sharesToBuy > 0){
                    double cost = shares_to_capital(sharesToBuy, close_stock[index_val]);

                    // Check if there's enough capital to buy shares.
                    if (cost > moving_capital){
                        std::cerr << "Not enough capital to buy shares." << std::endl;
                        isInvested = false; // Update investment status back to false
                    } else{
                        
                        // Buy shares and update capital.
                        shares += sharesToBuy; // Increase shares owned
                        moving_capital -= cost; // Decrease available capital
                        std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
                        sharesToBuy = 0; // Reset sharesToBuy
                        cost = 0; // Reset cost
                    }
                } else{
                    std::cout << "No shares can be bought" << std::endl;
                }
            } 
            
            // Check for sell signal: Momentum is negative and currently invested.
            else if (isInvested && momentum < 0){
                std::cout << "Sell signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
            
                // Sell all shares owned.
                isInvested = false; // Update investment status to false
                double earnings = shares_to_capital(shares, close_stock[index_val]);
                moving_capital += earnings; // Update capital with earnings
                std::cout << "Sold all shares. Capital: " << moving_capital << std::endl;
                shares = 0; // Reset shares owned
            }
        }
    }
}

void Momentum::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << capital << std::endl;

    // Runs dectection and finalisation of the strategy
    detect_momentum();
    finalise_simulation();
}

void Momentum::finalise_simulation(){

    // Sells all remaining shares if still invested. 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back(); // Get the last closing price
        double finalEarnings = shares_to_capital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        moving_capital += finalEarnings; // Update capital with final earnings
        final_capital = moving_capital; // Set final capital to current capital
        std::cout << "Final capital: $" << final_capital << std::endl;
        shares = 0; // Reset shares owned
    } else{
        final_capital = moving_capital; // Set final capital to current capital
        std::cout << "Final capital: $" << final_capital << std::endl;
    }
    profits = final_capital - capital; // Calculate profits from the investment
    set_profits(profits); // Set the profits in the investment class
}