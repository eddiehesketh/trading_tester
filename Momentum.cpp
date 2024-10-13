#include "Momentum.h"
#include <iostream>

Momentum::Momentum(std::string _start_date, float initial_capital, std::string stock_info, int period):Investment(initial_capital, stock_info){
    this->period = period;
    this-> start_date_ = _start_date;
    shares = 0;

    if (valid_start_date(start_date_)){
        investment_stratergy();
    } else{
        std::cout << "Non-existant start date" << std::endl;
    }
}

bool Momentum::valid_pay_freq(std::string freq){
    return true;
}

void Momentum::set_investment_type() {
    this->investment_type = "Momentum";
}

// int Momentum::date_index(const std::vector<std::string>& dates, const std::string& _start_date){
//     for (int i = 0; i < dates.size(); i++){
//         if (dates[i] == _start_date) {
//             return i;
//         }
//     }
//     return -1;
// }

double Momentum::calc_momentum(int period, int index_val){
    // Creates reference to close prices called close_stock
    const std::vector<float>& close_stock = get_close_prices();
    double sum = 0.0; 
    
    if (index_val < period - 1){
        return 1000000;
    }

    sum = close_stock[index_val] - close_stock[index_val - period + 1];
    return sum;
}

void Momentum::detect_momentum(){
    // Creates reference to close prices and dates called close_stock and current_date
    const std::vector<float>& close_stock = get_close_prices();
    const std::vector<std::string>& dates = get_dates();
    
    // Set conditions
    isInvested = false;
    int index_val = date_index(dates, start_date_);
    if (index_val == -1){
        std::cout << "Start date " << start_date_ << " Not found" << std::endl;
    } else{
        for (; index_val < close_stock.size(); index_val++){
            // Calculate the current moving averages for the current index
            double momentum = calc_momentum(period, index_val);
            if (momentum == 1000000){
            std::cout << "Invalid start date" << std::endl;
            break;
            }
            // Check for buy signal
            if (!isInvested && (momentum >= 0)){
                std::cout << "Buy signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
                isInvested = true;

                // Check for purchase shares
                int sharesToBuy = capital_to_shares(get_capital(), close_stock[index_val]);
                if (sharesToBuy > 0){
                    double cost = shares_to_capital(sharesToBuy, close_stock[index_val]);
                    if (cost > capital){
                        std::cerr << "Not enough capital to buy shares." << std::endl;
                        isInvested = false;
                    } else{
                        // Buy shares
                        shares += sharesToBuy;
                        capital -= cost;
                        std::cout << "Bought " << sharesToBuy << " shares." << std::endl;
                        sharesToBuy = 0;
                        cost = 0;
                    }
                } else{
                    std::cout << "No shares can be bought" << std::endl;
                }
            } 
            // Check for sell signal
            else if (isInvested && momentum < 0){
                std::cout << "Sell signal on " << dates[index_val] << ": Momentum " << momentum << std::endl;
            
                // Sell shares
                isInvested = false;
                double earnings = shares_to_capital(shares, close_stock[index_val]);
                capital += earnings;
                std::cout << "Sold all shares. Capital: " << capital << std::endl;
                shares = 0;
            }
        }
    }
}

void Momentum::investment_stratergy(){
    std::cout << "Investment strategy executed. Trading signals:\n";
    std::cout << "Initial capital: " << get_capital() << std::endl;

    // Runs dectection and finalisation of the strategy
    detect_momentum();
    finalize_simulation();
}

// int Momentum::capitalToShares(double capital, double closePrice){
//     // Determines if shares can be bought
//     if (capital <= 0){
//         std::cerr << "Error: Insufficient capital to buy shares." << std::endl;
//         return 0;
//     }
//     // Returns number of purchasable shares
//     return static_cast<int>(capital / closePrice);
// }

// double Momentum::sharesToCapital(int shares, double closePrice){
//     // Determines if shares can be sold
//     if (shares <= 0){
//         std::cerr << "Error: Cannot convert negative shares to capital." << std::endl;
//         return 0.0;
//     }
//     // Returns number of sellable shares
//     return shares * closePrice;
// }
void Momentum::finalize_simulation(){
    // Sells all remaining shares 
    if (isInvested && shares > 0){
        double lastClosePrice = stock_close.back();
        double finalCapital = shares_to_capital(shares, lastClosePrice);
        std::cout << "Converting remaining " << shares << " shares to capital at $" << lastClosePrice << " each." << std::endl;
        std::cout << "Final capital: $" << finalCapital << std::endl;
        capital += finalCapital;
        shares = 0;
    } else{
        std::cout << "Final capital: $" << capital << std::endl;
    }
}
