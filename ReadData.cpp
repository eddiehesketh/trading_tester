// Including relevant libraries.
#include "ReadData.h"
#include <iostream>
#include <algorithm>

// infroming program that the standard namespace will be used.
using namespace std;

// Read data class constructor.
ReadData::ReadData(string stock_info){

    set_stock_name(stock_info);

    // Initialising stock data based off name of csv file.
    set_stock_data(stock_info);
    
    // Using set titles function to allow getline to act on data points instead of the coloumn titles.
    set_titles();

    // Initialising line variable, which will change each while loop iteration.
    string line = "";

        // While loop iterating over each row.
        while (getline(stock_data, line)) {

            // Using stringstream to seperate the line extracted from getline function into into individual sets of numbers.
            stringstream ss(line);
            // Passing stringstream into subsequent data set functions.
            set_dates(ss); // Setting dates.
            set_stock_open(ss); // Setting open prices.
            set_stock_close(ss); // Setting close prices.
            set_stock_high(ss); // Setting high price.
            set_stock_low(ss); // Setting low price.
            set_stock_volume(ss); // Setting dailty volume.

            

    }


        // Closing stock data stream as it is no longer needed.
        stock_data.close();


}

// Clean money function takes in string and removes the dollar sign from the front.
string ReadData::clean_money(string value){

    //Uses erase function to erase the first index of the string value, being the dollar sign
    value.erase(value.begin());
    
    // Return the cleaned value, without dollar sign.
    return value;
}

// Clean value function removes any spaces or "" from the string, so that it only consists of characters and numbers.
string ReadData::clean_value(string value) {

    // Remove leading/trailing spaces using erase function
    value.erase(0, value.find_first_not_of(' '));  // Trims the leading spaces, from index 0.
    value.erase(value.find_last_not_of(' ') + 1);  // Trims the trailing spaces.

    // Remove surrounding quotes from the data.
    if (value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2); // Creates smaller substring excluding the quotes.
    }

    // Returns value, cleaned.
    return value;
}

// Clear commas function takes in string and removes all commas from it.
string ReadData::clear_commas(string value){

    // Uses remove function to push all commas to end of string.
    value.erase(remove(value.begin(), value.end(), ','), value.end()); // Then erases from the last n characters in the string which are commas.

    // Return value  without commas.
    return value;

}

// Set stock data function opens the file passed into the class.
void ReadData::set_stock_data(string stock_file_name){
    this->stock_data.open(stock_file_name); // Open the csv file passed in.
}

// Get stock data function returns stock data by reference.
ifstream& ReadData::get_stock_data(){
    if (!stock_data.is_open()) {
    std::cerr << "Error: Failed to open file " << name << std::endl;
} else {
    std::cout << "File " << name << " opened successfully." << std::endl;
}
    return this->stock_data; // Returns protected stock data.
}

// set titles function called first in constructor to extract titles, and allow the other data to be focused on.
void ReadData::set_titles(){
    getline(get_stock_data(), this->titles); // Use getline function to extract the titles.
}

// Set dates function takes in ss stringstream and appends date onto date vector.
void ReadData::set_dates(stringstream& ss){
    
    // Set temporary data string.
    string running_date;

    // Use getline to extract info from the end of most recent getline call to the next comma, and store it in the running date variavle
    getline(ss, running_date, ',');
    date.push_back(clean_value(running_date));
}

// Set stock open function, used to set the open stock prices protected vector.
void ReadData::set_stock_open(stringstream& ss){

    // Creating running open variable.
    string running_open;

    // Use getline funciton to read a string from the input stream ss, extracting data up until the next comma.
    getline(ss, running_open, ',');

    // Running open is cleaned, ready for numerical data type conversion.
    running_open = clean_value(running_open);

    // Checking if this process worked correctly for error handling.
    if (running_open == "#N/A" || running_open.empty()) {

        // Infomring user of the invalid data or error.
             std::cerr << "Invalid data for open price: " << running_open << std::endl;

        // If so, push a dafualt float value.
        stock_open.push_back(0.0f);
    } else {
        // If the data is valid, attempt to convert the cleaned string to a float.
        try {
            // Pushback value into stock open vector.
            stock_open.push_back(stof(clean_money(running_open))); // Cleans the dollar signs from the string and converts it into a float.

        } catch (const std::invalid_argument& e) { // If the conversion fails, catch the exception and print an error message.

            // print the error.
            std::cerr << "Invalid data for open price: " << running_open << std::endl;

            // Push back a default value
            stock_open.push_back(0.0f); 
        }
    }
}




// Set stock close function, used the set the protected stock close vector.
void ReadData::set_stock_close(stringstream& ss){

    // Create a running close string.
    string running_close;

    // Use getline funciton to read a string from the input stream ss, extracting data up until the next comma.
    getline(ss, running_close, ',');

    // Running close is cleaned, ready for numerical data type conversion.
    running_close = clean_value(running_close);

    // Checking if this process worked correctly for error handling.
    if (running_close == "#N/A" || running_close.empty()) {

        // Infomring user of the invalid data or error.
        std::cerr << "Invalid data for close price: " << running_close << std::endl;

        // If so, push a dafualt float value.
        stock_close.push_back(0.0f); 
    } else {
        // If the data is valid, attempt to convert the cleaned string to a float.
        try {
            stock_close.push_back(stof(clean_money(running_close)));  // Cleans the dollar signs from the string and converts it into a float.

        } catch (const std::invalid_argument& e) { // If the conversion fails, catch the exception and print an error message.

            // Inform user of error.
            std::cerr << "Invalid data for close price: " << running_close << std::endl;

            // Push back a defualt value.
            stock_close.push_back(0.0f); 
        }
    }
}

// Set stock high function, used to set the procted stock highs vector.
void ReadData::set_stock_high(stringstream& ss){

    // Creating a running high string.
    string running_high;

    // Use getline funciton to read a string from the input stream ss, extracting data up until the next comma.
    getline(ss, running_high, ',');

    // Running high is cleaned, ready for numerical data type conversion.
    running_high = clean_value(running_high);

    // Checking if this process worked correctly for error handling.
    if (running_high == "#N/A" || running_high.empty()) {

        // Infomring user of the invalid data or error.
        std::cerr << "Invalid data for high price: " << running_high << std::endl;

        // Pushing back a default value, to cover for the error.
        stock_high.push_back(0.0f);  
    } else {
        // If the data is valid, attempt to convert the cleaned string to a float.
        try {
            stock_high.push_back(stof(clean_money(running_high))); // Cleans the dollar signs from the string and converts it into a float.

        } catch (const std::invalid_argument& e) { // If the conversion fails, catch the exception and print an error message.

            // Inform user of error.
            std::cerr << "Invalid data for high price: " << running_high << std::endl;

            // Push back a default value.
            stock_high.push_back(0.0f);  
        }
    }
}

// Set stock low function, used to set the procted stock vector.
void ReadData::set_stock_low(stringstream& ss){

    // Creating a running low variable.
    string running_low;

    // Use getline funciton to read a string from the input stream ss, extracting data up until the next comma.
    getline(ss, running_low, ',');

    // Running low is cleaned, ready for numerical data type conversion.
    running_low = clean_value(running_low);

    // Checking if this process worked correctly for error handling.
    if (running_low == "#N/A" || running_low.empty()) {

        // If so, inform user of the error.
        std::cerr << "Invalid data for low price: " << running_low << std::endl;

        // Pushback a default value.
        stock_low.push_back(0.0f); 

    } else {
        // If the data is valid, attempt to convert the cleaned string to a float.
        try {
            stock_low.push_back(stof(clean_money(running_low))); // Cleans the dollar signs from the string and converts it into a float.

        } catch (const std::invalid_argument& e) { // If the conversion fails, catch the exception and print an error message.

            // Inform user of the error.
            std::cerr << "Invalid data for close price: " << running_low << std::endl;

            // Pushback a default value.
            stock_low.push_back(0.0f);  
        }
    }

}

// Set stock volume sets the protected stock vector.
void ReadData::set_stock_volume(stringstream& ss){

    // Creates a runnning volume string, which will be manipulated.
    string running_volume;

    // Use getline funciton to read a string from the input stream ss, extracting data up until the next comma.
    getline(ss, running_volume, '\n');
 
    // Checking if this process worked correctly for error handling.
    if (running_volume == "#N/A" || running_volume.empty()) {

        // If so, inform user of the error.
        std::cerr << "Invalid data for volume: " << running_volume << std::endl;

        // Push back a default float value.
        volume.push_back(0.0f); 

    } else {
        try {
            // If the data is valid, attempt to convert the cleaned string to a long long.
            volume.push_back(stoll(clean_money(clear_commas((running_volume))))); // Cleans are commas or quotations from the volume string.

        } catch (const std::invalid_argument& e) { // If the conversion fails, catch the exception and print an error message.

            // Inform user of the error.
            std::cerr << "Invalid data for volume: " << running_volume << std::endl;

            // Push back a defualt value.
            volume.push_back(0.0f);
        }
    }

}

// Get dates function, returns address for vector for better memory management. 
const vector<string>& ReadData::get_dates() const{
    return this->date; // Returns the proctected dates vector.
}

// Get open prices function, returns address for vector for better memory management. 
const vector<float>& ReadData::get_open_prices() const{
   return this->stock_open; // Returns the protected stock open vector.
}
// Get close prices function, returns address for vector for better memory management. 
const vector<float>& ReadData::get_close_prices() const{
    return this->stock_close;   // Returns the protected stock close vector.
}
// Get high prices function, returns address for vector for better memory management. 
const vector<float>& ReadData::get_stock_high() const{
    return this->stock_high;  // Returns the protected stock high vector.
}

// Get stock low function, returns address for vector for better memory management. 
const vector<float>& ReadData::get_stock_low() const{
    return this->stock_low; // Returns the protected stock low vector.
}

// Get stock volume function, returns address for vector for better memory management. 
const vector<long long>& ReadData::get_volume() const{
    return this->volume; // Returns the protected volume vector.
}

// Get name function to return the name of a given stock.
const string ReadData::get_name(){return this->name;}

// Set stock name function, based off file name.
void ReadData::set_stock_name(string file_name){

    // If statement checking the file name, and assigning the correspinding company stock name.
    if (file_name == "microsoft.csv"){ 
        this->name = "Microsoft"; // Sets to microsoft.
    } else if (file_name == "apple.csv"){
        this->name = "Apple"; // Sets to apple.
    } else if (file_name == "google.csv"){
        this->name = "Google"; // Sets to google.
    } else if (file_name == "nvidia.csv"){
        this->name = "Nvidia"; // Sets to nvidia.
    } else if (file_name == "tesla.csv"){
        this->name = "Tesla"; // Sets to tesla.
    } else if (file_name == "amazon.csv"){
        this->name = "Amazon"; // Sets to amazon.
    } else if (file_name == "berkshire.csv"){
        this->name = "Berkshire Hathaway"; // Sets to berkshire hathaway.
    } else if (file_name == "adobe.csv"){
        this->name = "Adobe"; // Sets to adobe..
    } else if (file_name == "costco.csv"){
        this->name = "Costco"; // Sets to costco.
    } else if (file_name == "mastercard.csv"){
        this->name = "Mastercard"; // Sets to mastercard.
    } else if (file_name == "coke.csv"){
        this->name = "Coca-Cola"; // Sets to coke.
    } else if (file_name == "netflix.csv"){
        this->name = "Netflix"; // Sets to netflix.
    } else if (file_name == "toyota.csv"){
        this->name = "Toyota"; // Sets to toyota.
    } else if (file_name == "pepsi.csv"){
        this->name = "Pepsi";  // Sets to pepsi.
    } else if (file_name == "mcdonalds.csv"){
        this->name = "McDonalds"; // Sets to mcdonalds.
    } else if (file_name == "shell.csv"){
        this->name = "Shell"; // Sets to shell.
    } else if (file_name == "caterpillar.csv"){
        this->name = "Caterpillar"; // Sets to caterpillar.
    } else if (file_name == "disney.csv"){
        this->name = "Walt Disney"; // Sets to disney.
    } else if (file_name == "uber.csv"){
        this->name = "Uber"; // Sets to uber.
    } else if (file_name == "bhp.csv"){
        this->name = "BHP Group"; // Sets to BHP.
    } else {
        this->name = "Unknown"; // Sets to unkown if file name is invalid, for error proofing.
    }
}


// Read Data destructor.
ReadData::~ReadData(){};