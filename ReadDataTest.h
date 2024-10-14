// Read data  unit testing class.


// Defining the class and including he read data class.
#ifndef READDATATEST_H
#define READDATATEST_H
#include "ReadData.h"


// Using the standard namespace.
using namespace std;


// Read data test class.
class ReadDataTest{

    public:

        // Run tests function to run all of the tests at once.
        void run_tests(){
            test_name();
            test_dates();
            test_open_prices();
            test_vector_length();
            test_high_prices();
            test_low_prices();
            test_volumes();

        }

        // Checking to see if the name initialisation is successful.
        void test_name(){
            ReadData r("coke.csv");
            
            if (r.get_name() != "Coca-Cola"){
                cout << "Name test failed" << endl;
            } else{
                cout << "Name test passed" << endl;
            }
        }

        // Checking if the start date and end date from the dates vectors are correct.
        void test_dates(){
            ReadData c("bhp.csv");

            if ((c.get_dates()[0] != "13/8/1997") || (c.get_dates()[c.get_dates().size()-1] != "10/6/2024")){
                cout << "Date test failed" << endl;
            } else {
                cout << "Date test passed" << endl;
            }
        }

        // Checking to see if the open prices for the first and last indexes are correct.
        void test_open_prices(){

            ReadData p("pepsi.csv");

            if (((static_cast<int>(round(p.get_open_prices()[0])) == 1)) && ((static_cast<int>(round(p.get_open_prices()[p.get_open_prices().size()-1])) == 170))){
                cout << "Open price test passed" << endl;
            } else {
                cout << "Open price test failed" << endl;
            }


        }
        
        // Checking to see if all of the vector lengths are equal, otherwise functionality will be faulty.
        void test_vector_length(){

            // Defining all stock files.
            vector<string> stock_files = {
                "microsoft.csv", "apple.csv", "google.csv", "nvidia.csv", "tesla.csv",
                "amazon.csv", "berkshire.csv", "adobe.csv", "costco.csv", "mastercard.csv",
                "coke.csv", "netflix.csv", "toyota.csv", "pepsi.csv", "mcdonalds.csv",
                "caterpillar.csv", "disney.csv", "uber.csv", "bhp.csv"
            };


            // Iterating over every single stock file, and checking if the vector lengths are the same.
            for (int i = 0; i < stock_files.size(); i++){

                ReadData a(stock_files[i]);

                int num_dates = a.get_dates().size();
                int num_open_prices = a.get_open_prices().size();
                int num_close_prices = a.get_close_prices().size();
                int num_volumes = a.get_volume().size();
                int num_highs = a.get_stock_high().size();
                int num_lows = a.get_stock_low().size();

                if ((num_lows == num_dates) && (num_dates == num_open_prices) && (num_open_prices == num_close_prices) && (num_close_prices == num_volumes) && (num_volumes == num_highs)){
                    cout << "Test of vector lengths for " << a.get_name() << " hisotrical stock data passed. " << endl;
                } else {
                    cout << "Test of vector lengths for " << a.get_name() << " historical stock data failed. " << endl;
                }


            }
        }

        // Testing if the high prices of the start and end index match what they are supposed to.
        void test_high_prices(){

            ReadData p("apple.csv");

            if (((static_cast<int>(round(p.get_stock_high()[0])) == 0)) && ((static_cast<int>(round(p.get_stock_high()[p.get_open_prices().size()-1])) == 197))){
                cout << "High price test passed" << endl;
            } else {
                cout << "High price test failed" << endl;
            }


        }

        // Testing if the low prices of the start and end index match what they are supposed to.
        void test_low_prices(){

            ReadData p("netflix.csv");

            if (((static_cast<int>(round(p.get_stock_low()[0])) == 1)) && ((static_cast<int>(round(p.get_stock_low()[p.get_stock_low().size()-1])) == 636))){
                cout << "Low price test passed" << endl;
            } else {
                cout << "Low price test failed" << endl;
            }


        }

        // Testing if the volumes of the start and end index match what they are supposed to.
        void test_volumes(){


            ReadData p("nvidia.csv");

            if ((((p.get_volume()[0]) == 2714686642)) && ((p.get_volume()[p.get_volume().size()-1] == 314162650))){
                cout << "Volume test passed" << endl;
            } else {
                cout << "Volume test failed" << endl;
            }


        }





        


};





#endif