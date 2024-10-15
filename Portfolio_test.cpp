#include "Investment.h"
#include "Portfolio.h"
#include "Dividend.h"
#include "SetDeposit.h"
#include <iostream>

using  namespace std;


int main(){

    Portfolio p;


    Investment* p1 = new SetDeposit("2/1/2020", "nvidia.csv", 1000);
    Investment* p2 = new Dividend("2/1/2020", 5000, "Quarterly", "nvidia.csv", true);
    Investment* p8 = new SetDeposit("2/1/2020", "coke.csv", 1000);
    Investment* p4 = new Dividend("2/1/2020", 5000, "Quarterly", "apple.csv", false);
    Investment* p5 = new SetDeposit("2/1/2020", "google.csv", 1000);
    Investment* p6 = new Dividend("2/1/2020", 5000, "Quarterly", "microsoft.csv", true);
    Investment* p7 = new Dividend("2/1/2020", 5000, "Quarterly", "microsoft.csv", true);



    p.add_investment(p1);
    p.add_investment(p2);
    p.add_investment(p8);
    p.add_investment(p4);
    p.add_investment(p5);
    p.add_investment(p6);
    p.add_investment(p7);


    cout << "current worth of first investment: " << p2->get_final_capital() << endl;
    cout << "current worth of second investment: " << p1->get_final_capital() << endl;
    cout << "current worth of third investment: " << p8->get_final_capital() << endl;
    cout << "current worth of fourth investment: " << p4->get_final_capital() << endl;
    cout << "current worth of fith investment: " << p5->get_final_capital() << endl;
    cout << "current worth of sixth investment: " << p6->get_final_capital() << endl;
    cout << "current worth of sixth investment: " << p7->get_final_capital() << endl;
    cout << "current portfolio value with all investments: " << p.get_portfolio_value() << endl;

    cout << "\n\n\n\n";

    // p.remove_investment(1);

    cout << "Current number of investments: " << p.get_count() << endl;
    cout << "current portfolio value with all investments: " << p.get_portfolio_value() << endl;

    Investment* p3 = new SetDeposit("2/1/2020", "nvidia.csv", 1000);
    p.add_investment(p3);

    cout << "current portfolio value with all investments: " << p.get_portfolio_value() << endl;

    p.write_portfolio_summary();



    // delete p1;
    // delete p2;
}