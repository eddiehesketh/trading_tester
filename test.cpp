#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // for cleaning spaces

using namespace std;

// Function to trim spaces and remove quotes from a string
string clean_value(string value) {
    // Remove leading/trailing spaces
    value.erase(0, value.find_first_not_of(' '));  // Trim leading spaces
    value.erase(value.find_last_not_of(' ') + 1);  // Trim trailing spaces

    // Remove surrounding quotes if present
    if (value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2);
    }

    return value;
}


string clean_money(string value){

        value.erase(value.begin());

        // cout << value << endl;

    return value;
}

string clear_commas(string value){
    value.erase(remove(value.begin(), value.end(), ','), value.end());

    return value;
}



int main() {
    // Open the CSV file
    ifstream stock_data("test_csvfile.csv");

    if (!stock_data.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    // Vectors to store the data
    vector<string> date;
    vector<float> stock_open;
    vector<float> stock_close;
    vector<float> stock_high;
    vector<float> stock_low;
    vector<long long> volume;
    string line, titles;

    // Read the first line (column titles)
    if (getline(stock_data, titles)) {
        cout << "Headers: " << titles << endl;
    }

    // Read each line of the CSV file
    while (getline(stock_data, line)) {
        stringstream ss(line);

        string running_date, running_open, running_close, running_high, running_low, running_volume;

        // Extract each value from the line by splitting on commas
        getline(ss, running_date, ',');
        getline(ss, running_open, ',');
        getline(ss, running_close, ',');
        getline(ss, running_high, ',');
        getline(ss, running_low, ',');
        getline(ss, running_volume, '\n');

        // Clean the values (remove quotes and extra spaces)
        date.push_back(clean_value(running_date));
        stock_open.push_back(stof(clean_money((clean_value(running_open)))));
        cout << running_open << endl;
        stock_close.push_back(stof(clean_money((clean_value(running_close)))));
        stock_high.push_back(stof(clean_money((clean_value(running_high)))));
        stock_low.push_back(stof(clean_money((clean_value(running_low)))));
        cout << running_volume << endl;
        volume.push_back(stoll(clean_money(clear_commas((clean_value(running_volume))))));
    }

    stock_data.close();

    // stock_open = clean_money(stock_open);



    // Print the open prices to verify the data is correctly extracted
    for (size_t i = 0; i < stock_open.size(); i++) {
        cout << "Date: " << date[i] << ", Open: " << stock_open[i] <<", Volume: " << volume[i] << endl;
    }

    return 0;
}
