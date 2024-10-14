#include "ReadDataTest.h"
#include "SetDepositTest.h"
#include "Investment.h"
#include "Dividend.h"
#include "DividendTest.h"
#include "Display.h"
#include "DisplayTest.h"
#include "Portfolio.h"
#include "PortfolioTest.h"

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



    return 0;

}