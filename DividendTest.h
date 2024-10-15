// Unit testing file for dividend class.


// Define the class and include relevant header files.
#ifndef DIVIDEND_TEST
#define DIVIDEND_TEST
#include "ReadData.h"
#include "Dividend.h"
#include "Investment.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


// Using standard namespace.
using namespace std;

class DividendTest {

    public:

        // Defining the run tests function which will be used to run the tests.
        void run_tests() {
            test_initial_capital();
            test_final_capital();
            test_valid_pay_freq();
            test_profits();
            test_investment_type();
            test_reinvest_status();
        }

        // test inital capital function.
        void test_initial_capital() {
            Dividend dividend("21/11/1989", 1000, "Quarterly", "apple.csv", false);

            // Iterate the check if the capital matches to the expected.
            if (dividend.get_capital() == 1000) {
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        // Test final capital function.
        void test_final_capital() {
            Dividend dividend("28/10/2005", 500, "Monthly", "test_csv_2.csv", true);

            // Check to see if the final capital aligns with the expected result.
            if (static_cast<int>(round(dividend.get_final_capital())) == 69223) {
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        // test profits function.
        void test_profits() {
            Dividend dividend("2/1/2020", 1000, "Quarterly", "microsoft.csv", false);

            // Checks to see if the profits algins with the expected profit.s
            if (static_cast<int>(round(dividend.get_profits())) == 1158) { // Assuming a known profit
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        // Test valid pay frequencey function.
        void test_valid_pay_freq() {
            Dividend dividend("2/1/2020", 1000, "Monthly", "nvidia.csv", false);

            // Check to see if the pay frequencey matches what it is supposed to be.
            if (dividend.get_pay_freq() == "Monthly") {
                cout << "Valid pay frequency test passed" << endl;
            } else {
                cout << "Valid pay frequency test failed" << endl;
            }
        }

        // Test investment type function.
        void test_investment_type() {
            Dividend dividend("6/6/2002", 1000, "Quarterly", "netflix.csv", false);

            // Checking if the investment type is valid.
            if (dividend.get_investment_type() == "Dividend") {
                cout << "Investment type test passed" << endl;
            } else {
                cout << "Investment type test failed" << endl;
            }
        }

        // Testing the reinvestment status function.
        void test_reinvest_status() {
            Dividend dividend("7/4/2014", 1000, "Monthly", "google.csv", true);

            // Checking it reinvestment status matches that of the constructor.
            if (dividend.get_reinvest_status()) { 
                cout << "Reinvest status test passed" << endl;
            } else {
                cout << "Reinvest status test failed" << endl;
            }
        }
};

#endif