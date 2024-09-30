#include "ReadData.h"
#include <iostream>

using namespace std;

// Read data class constructor.
ReadData::ReadData(string stock_info){

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

    // for (size_t i = 0; i < stock_open.size(); i++) {
    //     cout << "Date: " << date[i] << ", Open: " << stock_open[i] <<", Volume: " << volume[i] << endl;
    // }

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

void ReadData::set_stock_open(stringstream& ss){
    string running_open;
    getline(ss, running_open, ',');
    stock_open.push_back(stof(clean_money((clean_value(running_open)))));
}


void ReadData::set_stock_close(stringstream& ss){
    string running_close;
    getline(ss, running_close, ',');
    stock_close.push_back(stof(clean_money((clean_value(running_close)))));
}

void ReadData::set_stock_high(stringstream& ss){
    string running_high;
    getline(ss, running_high, ',');
    stock_high.push_back(stof(clean_money((clean_value(running_high)))));
}

void ReadData::set_stock_low(stringstream& ss){
    string running_low;
    getline(ss, running_low, ',');
    stock_low.push_back(stof(clean_money((clean_value(running_low)))));
}

void ReadData::set_stock_volume(stringstream& ss){
    string running_volume;
    getline(ss, running_volume, '\n');
    volume.push_back(stoll(clean_money(clear_commas((clean_value(running_volume))))));
}

vector<string>& ReadData::get_dates(){
    return this->date;
}


//vector<float>& ReadData::get_open_prices(){
//    return this->stock_open;
//}

vector<float>& ReadData::get_close_prices(){
    return this->stock_close;
}

vector<float>& ReadData::get_stock_high(){
    return this->stock_high;
}

vector<float>& ReadData::get_stock_low(){
    return this->stock_low;
}

vector<long long>& ReadData::get_volume(){
    return this->volume;
}






// ReadData::~ReadData(){
//     stock_data.close();
// }