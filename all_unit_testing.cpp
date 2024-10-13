#include "ReadDataTest.h"
#include "SetDepositTest.h"
#include "Investment.h"

#include <iostream>

using namespace std;


int main(){


    cout << "READ DATA TESTING: \n\n\n";

    ReadDataTest test1;

    test1.run_tests();

    cout << "\n\n\nSET DEPOSIT TESTING: \n\n\n";

    SetDepsoitTest test2;

    test2.run_tests();

    return 0;

}