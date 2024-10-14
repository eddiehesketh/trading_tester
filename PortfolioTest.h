#ifndef PORTFOLIOTEST_H
#define PORTFOLIOTEST_H

#include "Portfolio.h"
#include "SetDeposit.h"
#include "Dividend.h"
#include "Display.h"
#include <iostream>
#include <fstream>
#include <vector>

class PortfolioTest {
public:
    void run_tests() {
        test_add_investment();
        test_remove_investment();
        test_portfolio_value();
        test_portfolio_summary();
    }

    // Test adding an investment to the portfolio
    void test_add_investment() {
        Portfolio portfolio;
        SetDeposit* deposit = new SetDeposit("1/1/2020", "apple.csv", 1000);
        portfolio.add_investment(deposit);
        
        if (portfolio.get_count() == 1) {
            std::cout << "Add investment test passed." << std::endl;
        } else {
            std::cout << "Add investment test failed." << std::endl;
        }
    }

    // Test removing an investment from the portfolio
    void test_remove_investment() {
        Portfolio portfolio;
        SetDeposit* deposit1 = new SetDeposit("1/1/2020", "apple.csv", 1000);
        SetDeposit* deposit2 = new SetDeposit("1/1/2021", "tesla.csv", 2000);
        portfolio.add_investment(deposit1);
        portfolio.add_investment(deposit2);

        portfolio.remove_investment(0);

        if (portfolio.get_count() == 1) {
            std::cout << "Remove investment test passed." << std::endl;
        } else {
            std::cout << "Remove investment test failed." << std::endl;
        }
    }

    // Test if the portfolio value is updated correctly after adding investments
    void test_portfolio_value() {
        Portfolio portfolio;
        SetDeposit* deposit = new SetDeposit("2/1/2020", "apple.csv", 1000);
        Dividend* dividend = new Dividend("2/1/2020", 1000, "Monthly", "microsoft.csv", true);
        portfolio.add_investment(deposit);
        portfolio.add_investment(dividend);

        portfolio.set_portfolio_value();
        float expected_value = deposit->get_final_capital() + dividend->get_final_capital();

        if (portfolio.get_portfolio_value() == expected_value) {
            std::cout << "Portfolio value test passed." << std::endl;
        } else {
            std::cout << "Portfolio value test failed." << std::endl;
        }
    }

    // Test writing the portfolio summary to a file
    void test_portfolio_summary() {
        Portfolio portfolio;
        SetDeposit* deposit = new SetDeposit("2/1/2020", "apple.csv", 1000);
        Dividend* dividend = new Dividend("2/1/2020", 1000, "Monthly", "microsoft.csv", true);
        portfolio.add_investment(deposit);
        portfolio.add_investment(dividend);
        portfolio.write_portfolio_summary();

        std::ifstream file("investment_summary.txt");
        if (file) {
            std::cout << "Portfolio summary test passed." << std::endl;
        } else {
            std::cout << "Portfolio summary test failed." << std::endl;
        }
    }

};


#endif