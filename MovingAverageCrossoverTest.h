#ifndef SETDEPOSITTEST_H
#define SETDEPOSITTEST_H
#include "ReadData.h"
#include "MovingAverageCrossover.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class MovingAverageCrossoverTest{

    public:

        void run_tests(){

            test_initial_capital();
            test_final_capital();
            test_valid_pay_freq();
            test_profits();
            test_investment_type();

        }

        void test_initial_capital(){
            
            MovingAverageCrossover strat("2/1/2020", 10000, "microsoft.csv", 10, 20);

            if (strat.get_capital() == 1000){
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        void test_final_capital(){
            MovingAverageCrossover strat("12/12/1980", 2000, "apple.csv", 10, 40);

            if (strat.get_final_capital() == ???){
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        void test_profits(){
            MovingAverageCrossover strat("2/1/2020", 5000, "tesla.csv", 5, 20);

            if (strat.get_profits() == ???){
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        void test_valid_pay_freq(){
            MovingAverageCrossover strat("25/10/2015", 500, "nvidia.csv", 10, 20);

            if (strat.get_pay_freq() == true){
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