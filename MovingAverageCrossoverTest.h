// Moving Average Crossover unit testing.

// Defining the class and including relevant libraries.
#ifndef MOVINGAVERAGECROSSOVERTEST_H
#define MOVINGAVERAGECROSSOVERTEST_H
#include "ReadData.h"
#include "MovingAverageCrossover.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// Using standard namespace.
using namespace std;

// Moving Average Crossover Test class.
class MovingAverageCrossoverTest{

    public:
        
        // Run tests funcion to call all of the tests simeltaneously.
        void run_tests(){

            test_initial_capital();
            test_final_capital();
            test_valid_pay_freq();
            test_profits();
            test_investment_type();

        }

        // Testing if the intial capital is correctly set.
        void test_initial_capital(){
            
            MovingAverageCrossover strat("2/1/2020", 10000, "microsoft.csv", 10, 20);

            if (strat.get_capital() == 10000){
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        // Testing if the final capital matches that of what it is expected to.
        void test_final_capital(){
            MovingAverageCrossover strat("12/12/2001", 2000, "apple.csv", 10, 40);
            
            if (static_cast<int>(round(strat.get_final_capital())) == 217875){
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        // Testing if the profits match what it is expected to.
        void test_profits(){
            MovingAverageCrossover strat("2/1/2020", 5000, "tesla.csv", 5, 20);
            
            if (static_cast<int>(round(strat.get_profits())) == 28159){
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        void test_valid_pay_freq(){
            MovingAverageCrossover strat("14/12/2015", 500, "nvidia.csv", 10, 20);

            if (strat.get_pay_freq() == "Once off"){
                cout << "Valid pay frequency test passed" << endl;
            } else {
                cout << "Valid pay frequency test failed" << endl;
            }
        }

        void test_investment_type(){
            MovingAverageCrossover strat("2/1/2020", 1000, "google.csv", 20, 50);

            if (strat.get_investment_type() == "Moving Average Crossover"){
                cout << "Investment type test passed" << endl;
            } else {
                cout << "Investment type test failed" << endl;
            }
        }
};

#endif