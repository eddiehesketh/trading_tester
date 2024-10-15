#include "MovingAverageCrossover.h"
#include <iostream>

// Moving average crossover constuctor, taking in a start data, stock info, and capital amount.
MovingAverageCrossover::MovingAverageCrossover(std::string _start_date, float initial_capital, std::string stock_info_, int period1, int period2)
    : Investment(initial_capital, stock_info_){

    // Setting the investment type from the constructor.
    set_investment_type();

    // Setting the pay frequency to once off.
    set_pay_freq("Once off");

    // Initializing the moving average periods and other member variables.
    this->Period1 = period1; // Shorter moving average period
    this->Period2 = period2; // Longer moving average period
    this->start_date_ = _start_date; // Starting date for the investment strategy
    this->moving_capital = capital; // Initial capital for investment
    shares = 0; // No shares initially owned

    // Determines which of the two periods is larger
    large_period(period1, period2);

    // Checking if there is a valid start date.
    if (valid_start_date(start_date_)){

        // if there is a valid start date, the investment stratergy is called.
        investment_stratergy();
    } else{

        // If not a valid start date display "Non-existant start date"
        std::cout << "Non-existant start date" << std::endl;
    }
}

bool MovingAverageCrossover::valid_pay_freq(std::string freq){

    // Checks if the frequencey is once off.
    if (freq == "Once off"){

        // If so return true.
        return true; 
    }

    // If not return false.
    return false;
}

void MovingAverageCrossover::set_investment_type(){
    
    // Sets the investment type to "Moving Average Crossover".
    this->investment_type = "Moving Average Crossover";
}

void MovingAverageCrossover::large_period(int period1, int period2){

    // Determines which of the two period inputs is larger.
    if (period1 > period2) {
        longPeriod = period1; // Set long period
        shortPeriod = period2; // Set short period
    } else {
        longPeriod = period2; // Set long period
        shortPeriod = period1; // Set short period
    }
}

double MovingAverageCrossover::moving_average(int period, int index_val){

    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0; // Variable to hold the sum of prices

    // If the index is less than the period, return a high value indicating invalid calculation.
    if (index_val < period - 1){
        return 1000000;
    }

    // Calculate and return the sum of the prices for the moving average
    for (int i = index_val; i >= (index_val - period + 1); i--){
        sum += close_stock[i]; // Add each price in the period to the sum
    }
    return sum / period; // Return the calculated moving average
}

void MovingAverageCrossover::detect_crossover(){
    
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();

    // Set conditions
    double previousShortMA = 0;
    double previousLongMA = 0;
    isInvested = false; // Track if currently invested
    int index_val = date_index(dates, start_date_); // Get index of the start date
    
    // Check if the start date is found in the dates vector.
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{

        // Iterate through the close prices starting from the index of the start date.
        for (; index_val < close_stock.size(); index_val++){

            // Calculate the current moving averages for the current index.
            double shortMA = moving_average(shortPeriod, index_val);
            double longMA = moving_average(longPeriod, index_val);

            // Check if the moving averages are valid.
            if (shortMA == 1000000 || longMA == 1000000){
                std::cout << "Invalid start date" << std::endl; // Invalid moving average calculation
                break;
            }

            // Check for buy signal: Short MA crosses above Long MA.
            if (!isInvested && (previousShortMA <= previousLongMA && shortMA > longMA && previousShortMA !=0)){
                // std::cout << "Buy signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed above LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
                isInvested = true; // Update investment status to true

                // Check how many shares can be purchased with the available capital.
                int sharesToBuy = capital_to_shares(moving_capital, close_stock[index_val]);
                if (sharesToBuy > 0){
                    double cost = shares_to_capital(sharesToBuy, close_stock[index_val]);

                    // Check if there's enough capital to buy shares.
                    if (cost > moving_capital){
                        // std::cerr << "Not enough capital to buy shares." << std::endl;
                        isInvested = false; // Update investment status back to false
                    } else {

                        // Buy shares and update capital.
                        shares += sharesToBuy; // Increase shares owned
                        moving_capital -= cost; // Decrease available capital
                        // std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
                        sharesToBuy = 0; // Reset sharesToBuy
                        cost = 0; // Reset cost
                    }
                } else{
                    // std::cout << "No shares can be bought" << std::endl;
                }
            } 

            // Check for sell signal: Short MA crosses below Long MA.
            else if (isInvested && (previousShortMA >= previousLongMA && shortMA < longMA)){
                // std::cout << "Sell signal on " << dates[index_val] << ": ShortMA " << shortMA << " crossed below LongMA " << longMA << ", Previous ShortMA " << previousShortMA << " Previous LongMA " << previousLongMA << std::endl;
            
                // Sell all shares owned.
                isInvested = false; // Update investment status to false
                double earnings = shares_to_capital(shares, close_stock[index_val]);
                moving_capital += earnings; // Update capital with earnings
                // std::cout << "Sold all shares. Capital: " << moving_capital << std::endl;
                shares = 0; // Reset shares owned
            }

            // Update previous moving averages for the next iteration
            previousShortMA = shortMA;
            previousLongMA = longMA;
        }
    }
}

// Implementing the overidden investment stratergy function.
void MovingAverageCrossover::investment_stratergy(){
    // std::cout << "Investment strategy executed. Trading signals:\n";
    // std::cout << "Initial capital: " << capital << std::endl;
    
    // Runs dectection and finalisation of the strategy
    detect_crossover();
    finalise_simulation();
}

void MovingAverageCrossover::finalise_simulation(){

    // Sells all remaining shares if still invested. 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back(); // Get the last closing price
        double finalEarnings = shares_to_capital(shares, lastClosePrice); // Calculate earnings from remaining shares
        // std::cout << "Converting remaining " << shares << " shares to capital" << std::endl;
        moving_capital += finalEarnings; // Update capital with final earnings
        final_capital = moving_capital; // Set final capital to current capital
        // std::cout << "Final capital: $" << final_capital << std::endl;
        shares = 0; // Reset shares owned
    } else{
        final_capital = moving_capital; // Set final capital to current capital
        // std::cout << "Final capital: $" << final_capital << std::endl;
    }
    profits = final_capital - capital; // Calculate profits from the investment
    set_profits(profits); // Set the profits in the investment class
}