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

using namespace std;

class DividendTest {

    public:

        void run_tests() {
            test_initial_capital();
            test_final_capital();
            test_valid_pay_freq();
            test_profits();
            test_investment_type();
            test_reinvest_status();
        }

        void test_initial_capital() {
            Dividend dividend("21/11/1989", 1000, "Quarterly", "apple.csv", false);

            if (dividend.get_capital() == 1000) {
                cout << "Initial capital test passed" << endl;
            } else {
                cout << "Initial capital test failed" << endl;
            }
        }

        void test_final_capital() {
            Dividend dividend("28/10/2005", 500, "Monthly", "test_csv_2.csv", true);

            if (static_cast<int>(round(dividend.get_final_capital())) == 69223) { // Assuming a known result
                cout << "Final capital test passed" << endl;
            } else {
                cout << "Final capital test failed" << endl;
            }
        }

        void test_profits() {
            Dividend dividend("2/1/2020", 1000, "Quarterly", "microsoft.csv", false);

            if (static_cast<int>(round(dividend.get_profits())) == 158) { // Assuming a known profit
                cout << "Profits test passed" << endl;
            } else {
                cout << "Profits test failed" << endl;
            }
        }

        void test_valid_pay_freq() {
            Dividend dividend("1/1/2020", 1000, "Monthly", "nvidia.csv", false);

            if (dividend.get_pay_freq() == "Monthly") {
                cout << "Valid pay frequency test passed" << endl;
            } else {
                cout << "Valid pay frequency test failed" << endl;
            }
        }

        void test_investment_type() {
            Dividend dividend("6/6/2002", 1000, "Quarterly", "netflix.csv", false);

            if (dividend.get_investment_type() == "Dividend") {
                cout << "Investment type test passed" << endl;
            } else {
                cout << "Investment type test failed" << endl;
            }
        }

        void test_reinvest_status() {
            Dividend dividend("7/4/2014", 1000, "Monthly", "google.csv", true);

            // Assuming true is for reinvestment status
            if (dividend.get_reinvest_status()) { 
                cout << "Reinvest status test passed" << endl;
            } else {
                cout << "Reinvest status test failed" << endl;
            }
        }
};

#endif