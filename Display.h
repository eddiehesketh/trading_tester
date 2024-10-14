// Display class is used to format information from read data into a form which can be easily displayed by the GUI.

// Defining the class and including read data.
#ifndef DISPLAY_H
#define DISPLAY_H
#include "ReadData.h" 

// Display class inherits from Read Data class.
class Display: public ReadData{

    public:

        // Display constructor.
        Display(std::string stock);

        // Function to return the opening stock price of a specific day.
        std::string single_open_prices(int day) const;

        // Function to return the closing stock price of a specific day.
        std::string single_close_prices(int day) const;

        // Function to return the date for a specific index.
        std::string single_dates(int day) const;

        // Function to return the trading volume for a specific day.
        std::string single_volumes(int day) const;

        // Function to calculate and return the daily percentage change, open to close, of the stock price for a specific day.
        std::string daily_change(int day) const;

        // Helper function to format the daily percentage change.
        std::string clean_daily_change(bool status, std::string value) const;




};

#endif