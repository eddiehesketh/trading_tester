#ifndef RISKASSESMENTTEST_H
#define RISKASSESMENTTEST_H
#include "RiskAssesment.h"
#include "Investment.h"
#include "SetDeposit.h"
#include "Dividend.h"
#include "MovingAverageCrossover.h"
#include "Momentum.h"

class RiskAssesmentTest{

    public:
        void run_tests(){
            test_momentum();
            test_dividend();
            test_moving_average_crossover();
            test_set_deposit();

        }

        void test_momentum(){
            Investment* test = new Momentum("20/1/2021", 500, "costco.csv", 50);

            RiskAssesment risk(test);

            if (risk.get_risk_rating() == "High"){
                std::cout << "Momentum risk rating test passed." << std::endl;
            } else {
                std::cout << "Momentum risk rating test failed." << std::endl;
            }
        }

        void test_moving_average_crossover(){
            Investment* test = new MovingAverageCrossover("10/5/2023", 500, "test_csv_2.csv", 10, 20);

            RiskAssesment risk(test);

            if (risk.get_risk_rating() == "High"){
                std::cout << "Moving average crossover risk rating test passed." << std::endl;
            } else {
                std::cout << "Moving average crossover risk rating test failed." << std::endl;
            }
        }


        void test_set_deposit(){
            Investment* test = new SetDeposit("2/1/2020", "microsoft.csv", 1000);

            RiskAssesment risk(test);

            if (risk.get_risk_rating() == "Low to medium"){
                std::cout << "Set deposit risk rating test passed." << std::endl;
            } else {
                std::cout << "Set deposit risk rating test failed." << std::endl;
            }
        }

        void test_dividend(){
            Investment* test = new Dividend("2/1/2020", 1000, "Quarterly", "microsoft.csv", false);

            RiskAssesment risk(test);

            if (risk.get_risk_rating() == "Low"){
                std::cout << "Dividend risk rating test passed." << std::endl;
            } else {
                std::cout << "Dividend risk rating test failed." << std::endl;
            }
        }

        
        
};








#endif
