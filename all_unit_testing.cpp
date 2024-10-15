#include "ReadDataTest.h"
#include "SetDepositTest.h"
#include "Investment.h"
#include "Dividend.h"
#include "DividendTest.h"
#include "Display.h"
#include "DisplayTest.h"
#include "Portfolio.h"
#include "PortfolioTest.h"
#include "RiskAssesment.h"
#include "RiskAssesmentTest.h"
#include "MovingAverageCrossoverTest.h"
#include "MomentumTest.h"

#include <iostream>

using namespace std;


int main(){

    // Tests for read data.
    cout << "READ DATA TESTING: \n\n\n";

    // Calling read data test constructor.
    ReadDataTest test1;

    // Running tests.
    test1.run_tests();

     // Tests for set depost.
    cout << "\n\n\nSET DEPOSIT TESTING: \n\n\n";

    SetDepsoitTest test2;

     // Running tests.
    test2.run_tests();

     // Tests for dividend.
    cout << "\n\n\nDIVIDEND TESTING: \n\n\n";

    DividendTest test3;

     // Running tests.
    test3.run_tests();


     // Tests for display data.
    cout << "\n\n\n DISPLAY DATA TESTING: \n\n\n";

    DisplayTest test4;

     // Running tests.
    test4.run_tests();

    // Tests for portfolio.
    cout << "\n\n\n PORTFOLIO TESTING \n\n\n";
    PortfolioTest test5;

    test5.run_tests();

    // Tests for risk assesment class.
    cout << "\n\n\n RISK ASSESMENT TESTING \n\n\n";

    RiskAssesmentTest test6;
    test6.run_tests();

    // Tests for moving average crossover.
    cout << "MOVING AVERAGE CROSSOVER TESTING: \n\n\n";

    // Calling moving average test constructor.
    MovingAverageCrossoverTest test7;

    // Running tests.
    test7.run_tests();

    // Tests for momentum.
    cout << "MOMENTUM TESTING: \n\n\n";

    // Calling momentum test constructor.
    MomentumTest test8;

    // Running tests.
    test7.run_tests();

    return 0;

}