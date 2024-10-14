// Set deposit unit testing.

// Defining the class and including relevant libraries.
#ifndef SETDEPOSITTEST_H
#define SETDEPOSITTEST_H
#include "ReadData.h"
#include "SetDeposit.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

// Using standard namespace.
using namespace std;


// Set Deposit Test class.
class SetDepsoitTest{

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
            
            SetDeposit deposit("2/1/2020", "microsoft.csv", 1000);

            if (deposit.get_capital() == 1000){
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        // Testing if the final capital matches that of what it is expected to.
        void test_final_capital(){
            SetDeposit deposit("12/12/1980", "apple.csv", 1);


            if (static_cast<int>(round(deposit.get_profits())) == 1514){
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        // Testing if the profits match what it is expected to.
        void test_profits(){
            SetDeposit deposit("2/1/2020", "tesla.csv", 1000);

            if (static_cast<int>(round(deposit.get_profits())) == 5221){
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        // Testing if the pay frequencey is automatically set to once off like it should be.
        void test_valid_pay_freq(){
            SetDeposit deposit("25/10/2015", "nvidia.csv", 1000);

            if (deposit.get_pay_freq() == "Once off"){
                cout << "Valid pay frequency test passed" << endl;
            } else {
                cout << "Valid pay frequency test failed" << endl;
            }
        }

        // Ensuring the investment type is set to deposit.
        void test_investment_type(){
            SetDeposit deposit("2/1/2020", "google.csv", 1000);

            if (deposit.get_investment_type() == "Deposit"){
                cout << "Investment type test passed" << endl;
            } else {
                cout << "Investment type test failed" << endl;
            }
        }

};





#endif