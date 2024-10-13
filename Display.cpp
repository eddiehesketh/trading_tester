#include "ReadData.h"
#include "Display.h"
#include <iostream>

using namespace std;

// Constructor for the Display class, initializing the base class ReadData with the stock name.
Display::Display(std::string stock): ReadData(stock){};


// Function to get the open price for a specific day, format it as a string, and return it.
string Display::single_open_prices(int day) const {


    // debugging - check if openPrices is empty
    auto openPrices = get_open_prices();
    if (openPrices.empty()) {

        // If empty, inform user of error.
        std::cerr << "Error: open prices data is empty for stock." << std::endl;
        return "$0.00";  // Return a default value.
    }

    // Get the open price for the specified day.
    float price1 = get_open_prices()[get_open_prices().size()-day];

    // Convert the price to a string.
    string price = to_string(price1);

    // Remove unnecessary decimal places, keeping only two.
    price.erase(price.find_first_of(".")+3);

    // Insert a dollar sign.
    price.insert(0, "$");

    // Return the formatted price.
    return price;

}

// Function to retrieve the close price for a specific day, format it as a string, and return it.
string Display::single_close_prices(int day) const {

    // Get the close price for the specified day.
    float price1 = get_close_prices()[get_close_prices().size()-day];

    // Convert the price to a string.
    string price = to_string(price1);

    // Remove unnecessary decimal places, keeping only two.
    price.erase(price.find_first_of(".")+3);

    // Insert a dollar sign
    price.insert(0, "$");

    // Return price to caller.
    return price;

}

// Function to return the date for a specific day from the stored date vector.
string Display::single_dates(int day) const {
    return get_dates()[get_dates().size()-day];
}

// Function to retrieve the trading volume for a specific day, format it as a string, and return it.
string Display::single_volumes(int day) const {

    // Get the trading volume for the specified day.
    float volume = get_volume()[get_volume().size()-day];

    // Convert the volume to a string.
    string str_vol = to_string(volume);

     // Remove the decimal part from the volume.
    str_vol.erase(str_vol.find_first_of("."));

    // Insert a dollar sign at the beginning of the string.
    str_vol.insert(0, "$");

    // Return the formatted volume.
    return str_vol;

}

// Function to calculate and return the percentage change between the open and close prices.
string Display::daily_change(int day) const {

    // Initialize the change variable.
    float change = 0;

    // Get references to the open and close prices vectors.
    const vector<float>& open = get_open_prices();
    const vector<float>& close = get_close_prices();

    // Check if the specified day is out of bounds for the vectors.
    if (day >= open.size() || day >= close.size() || day < 0) {
        return "N/A";   // Return "N/A" if the day is invalid.
    }

    // Get the index corresponding to the specified day.
    int index = open.size() - day;

    // Initalise return value string.
    string return_value = "";

    // Calculate the percentage change from open to close price.
    change = ((close[index] - open[index]) / open[index]) * 100;

    // Convert the change value to a string.
    return_value = to_string(change);

    // Determine if the change is positive or negative, and format the result.
    if (close[index] >= open[index]){

        // Format and return the positive change.
        return clean_daily_change(true, return_value);

    } else if (close[index] < open[index]){

        // Format and return the negative change.
        return clean_daily_change(false, return_value);

    }

    // If there was an issue, return "N/A"
    return "N/A";

}


// Helper function to format the daily percentage change by adding the correct sign
string Display::clean_daily_change(bool status, string value) const {

    if (status){

        // If the change is positive, add a + to the start of the value.
        value.insert(0, "+");

        // Limit the string to two decimal places.
        value.erase(value.find_first_of(".")+3);

        // Add a % to the end.
        value.append("%");

        // Return the formatted value.
        return value;

    } else if (!status){
        // No need to add a negative sign as it will already be there.

        // Limit the string to two decimal places.
        value.erase(value.find_first_of(".")+3);

        // Add a % to the end of the string.
        value.append("%");

        // Return value to caller.
        return value;
    }

    // if error occured, return null.
    return NULL;
}

