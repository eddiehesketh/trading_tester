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

int main() {
    // Open the CSV file
    ifstream stock_data("test_csvfile.csv");

    if (!stock_data.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    // Vectors to store the data
    vector<string> date;
    vector<string> stock_open;
    vector<string> stock_close;
    vector<string> stock_high;
    vector<string> stock_low;
    vector<string> volume;
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
        getline(ss, running_volume, ',');

        // Clean the values (remove quotes and extra spaces)
        date.push_back(clean_value(running_date));
        stock_open.push_back(clean_value(running_open));
        stock_close.push_back(clean_value(running_close));
        stock_high.push_back(clean_value(running_high));
        stock_low.push_back(clean_value(running_low));
        volume.push_back(clean_value(running_volume));
    }

    stock_data.close();

    // Print the open prices to verify the data is correctly extracted
    for (size_t i = 0; i < stock_open.size(); i++) {
        cout << "Date: " << date[i] << ", Open: " << stock_open[i] << endl;
    }

    return 0;
}
