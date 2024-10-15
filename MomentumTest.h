// Momentum unit testing.
#ifndef MOMENTUMTEST_H
#define MOMENTUMTEST_H
#include "ReadData.h"
#include "SetDeposit.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// Using standard namespace.
using namespace std;

// Momentum Test class.
class MomentumTest{

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
            
            Momentum strat("2/1/2020", 10000, "microsoft.csv", 10);

            if (strat.get_capital() == 10000){
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        // Testing if the final capital matches that of what it is expected to.
        void test_final_capital(){
            Momentum strat("12/12/2001", 100, "apple.csv", 15);

            if (static_cast<int>(round(strat.get_profits())) == 8915){
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        // Testing if the profits match what it is expected to.
        void test_profits(){
            Momentum strat("2/1/2020", 1000, "tesla.csv", 15);

            if (static_cast<int>(round(strat.get_profits())) == 9030){
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        // Testing if the pay frequencey is automatically set to once off like it should be.
        void test_valid_pay_freq(){
            Momentum strat("26/6/2018", 1000, "nvidia.csv", 20);

            if (strat.get_pay_freq() == "Once off"){
                cout << "Valid pay frequency test passed" << endl;
            } else {
                cout << "Valid pay frequency test failed" << endl;
            }
        }

        // Ensuring the investment type is set to deposit.
        void test_investment_type(){
            Momentum strat("2/1/2020", 10000, "google.csv", 10);

            if (strat.get_investment_type() == "Momentum"){
                cout << "Investment type test passed" << endl;
            } else {
                cout << "Investment type test failed" << endl;
            }
        }

};





#endif