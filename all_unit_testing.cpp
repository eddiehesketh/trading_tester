#include "ReadDataTest.h"
#include "SetDepositTest.h"
#include "Investment.h"
#include "Dividend.h"
#include "DividendTest.h"
#include "Display.h"
#include "DisplayTest.h"

#include <iostream>

using namespace std;


int main(){


    cout << "READ DATA TESTING: \n\n\n";

    ReadDataTest test1;

    test1.run_tests();

    cout << "\n\n\nSET DEPOSIT TESTING: \n\n\n";

    SetDepsoitTest test2;

    test2.run_tests();

    cout << "\n\n\nDIVIDEND TESTING: \n\n\n";

    DividendTest test3;

    test3.run_tests();


    cout << "\n\n\n DISPLAY DATA TESTING: \n\n\n";

    DisplayTest test4;

    test4.run_tests();




    return 0;

}