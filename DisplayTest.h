#ifndef DISPLAYTEST_H
#define DISPLAYTEST_H
#include "Display.h"
#include <iostream>
#include <vector>
#include <string>

class DisplayTest {
public:
    void run_tests() {
        test_single_open_prices();
        test_single_close_prices();
        test_single_dates();
        test_single_volumes();
        test_daily_change();
    }

    void test_single_open_prices() {
        Display display("test_csv_2.csv");
        
        std::vector<std::string> expected_open = {"$184.22", "$187.14", "$193.89", "$194.13", "$192.49", "$193.61", "$195.17"};

        for (int i = 1; i < 8; i++) {
            if (display.single_open_prices(i) == expected_open[i - 1]) {
                std::cout << "Open price day " << i << " test passed." << std::endl;
            } else {
                std::cout << "Open price day " << i << " test failed." << std::endl;
            }
        }
    }

    void test_single_close_prices() {
        Display display("test_csv_2.csv");

        std::vector<std::string> expected_close = {"$184.25", "$185.63", "$192.52", "$193.58", "$193.14", "$193.05", "$193.60"};

        for (int i = 1; i < 8; i++) {
            if (display.single_close_prices(i) == expected_close[i - 1]) {
                std::cout << "Close price day " << i << " test passed." << std::endl;
            } else {
                std::cout << "Close price day " << i << " test failed." << std::endl;
            }
        }
    }

    void test_single_dates() {
        Display display("test_csv_2.csv");

        std::vector<std::string> expected_dates = {"3/1/2024", "2/1/2024", "29/12/2023", "28/12/2023", "27/12/2023", "26/12/2023", "22/12/2023"};

        for (int i = 1; i < 8; i++) {
            if (display.single_dates(i) == expected_dates[i - 1]) {
                std::cout << "Date day " << i << " test passed." << std::endl;
            } else {
                std::cout << "Date day " << i << " test failed." << std::endl;
            }
        }
    }

    void test_single_volumes() {
        Display display("test_csv_2.csv");

        std::vector<std::string> expected_volume = {"$58414460", "$82488672", "$42672148", "$34049896", "$48087680", "$28919310", "$37149568"};

        for (int i = 1; i < 8; i++) {
            if (display.single_volumes(i) == expected_volume[i - 1]) {
                std::cout << "Volume day " << i << " test passed." << std::endl;
            } else {
                std::cout << "Volume day " << i << " test failed." << std::endl;
            }
        }
    }

    void test_daily_change() {
        Display display("test_csv_2.csv");

        std::vector<std::string> expected_change = {"+0.01%", "-0.80%", "-0.70%", "-0.28%", "+0.34%", "-0.28%", "-0.80%"};

        for (int i = 1; i < 8; i++) {
            if (display.daily_change(i) == expected_change[i - 1]) {
                std::cout << "Daily change day " << i << " test passed." << std::endl;
            } else {
                std::cout << "Daily change day " << i << " test failed." << std::endl;
            }
        }
    }
};

#endif // DISPLAY_TEST_H