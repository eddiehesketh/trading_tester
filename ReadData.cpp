#include "ReadData.h"
#include <iostream>

using namespace std;


ReadData::ReadData(string stock_info){
    set_stock_data(stock_info);
    set_titles();

    string line = "";

        while (getline(stock_data, line)) {
            stringstream ss(line);
            set_dates(ss);
            set_stock_open(ss);
            set_stock_close(ss);
            set_stock_high(ss);
            set_stock_low(ss);
            set_stock_volume(ss);

    }

    for (size_t i = 0; i < stock_open.size(); i++) {
        cout << "Date: " << date[i] << ", Open: " << stock_open[i] <<", Volume: " << volume[i] << endl;
    }

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

void ReadData::set_stock_data(string stock_file_name){
    this->stock_data.open(stock_file_name);
}

ifstream& ReadData::get_stock_data(){
    return this->stock_data;
}

void ReadData::set_titles(){
    getline(get_stock_data(), this->titles);
}

void ReadData::set_dates(stringstream& ss){
    string running_date;
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




// ReadData::~ReadData(){
//     stock_data.close();
// }