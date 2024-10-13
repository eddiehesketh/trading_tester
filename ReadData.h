// Read Data class is the base class for this project, it will store relevant stock data for a given stock, which can 
// later be manipulated for different investment stratergies.


// Define the ReadData class and inclue relevant libraries.
#ifndef READDATA_H
#define READDATA_H
#include <iostream>  // For input/ output operations.
#include <vector> // Allows for the use of the std::vector library, used to store data.
#include <fstream> // Used to handle file input and output operations.
#include <sstream> // Used for string manipulation when reading .csv files.
#include <string> // Allows string data type to be used.


// Read Data class.
class ReadData{

    protected:

        // Defining protetected class elements.
        std::string titles; // Titles of each coloumn of csv file.
        std::string name; // Name of the stock being analysed.
        std::vector<std::string> date; // Vector containing dates.
        std::vector<float> stock_open; // Vector containing open prices.
        std::vector<float> stock_close; // Vector containing close prices.
        std::vector<float> stock_high; // Vector containing high prices.
        std::vector<float> stock_low; // Vector containing low prices.
        std::vector<long long> volume;   // Vector containing stock volumes.
        std::ifstream stock_data; // Entire file content.


    
    public:

        // Read data contructor, taking in the file name.
        ReadData(std::string stock_info);
        ReadData();

        // Clean value function, removing elements which prevent conversion to numerical datatype.
        std::string clean_value(std::string value);

        // Clean money function, removing dollar signs from strings.
        std::string clean_money(std::string value);

        // Clear commas funciton, removing commas from strings.
        std::string clear_commas(std::string volume);

        // Set titles function, used to set the protected titles variable.
        void set_titles();

        // Set stock data functon used to set the protected stock data variable
        void set_stock_data(std::string stock_file_name);

        // Returns the stock data from the protected stock data variable.
        std::ifstream& get_stock_data();

        // A range of set functions, used to set corresponding protected variables.
        void set_dates(std::stringstream& ss); // Sets the protected dates.
        void set_stock_open(std::stringstream& ss); // Sets the protected open prices.
        void set_stock_close(std::stringstream& ss); // Sets the protected close prices.
        void set_stock_high(std::stringstream& ss); // Sets the protected high prices.
        void set_stock_low(std::stringstream& ss); // Sets the protected low prices.
        void set_stock_volume(std::stringstream& ss); // Sets the protected volumes.
        void set_stock_name(std::string name); // Sets the protectected stock name.


        // A rangre of  get functions, to return corresponding protectd variables, and reference adresses to vectors, for efficient memory management.
        const std::string get_name(); // Gets the protected name variable.
        const std::vector<std::string>& get_dates() const; // Gets the protected dates vector.
        const std::vector<float>& get_open_prices() const; // Gets the protected open prices vector.
        const std::vector<float>& get_close_prices() const; // Gets the protected close prices vector.
        const std::vector<float>& get_stock_high() const; // Gets the protected stock high vector.
        const std::vector<float>& get_stock_low() const; // Gets the protected stock low vector.
        const std::vector<long long>& get_volume() const; // Gets the protected volumes vector.

    
        // Read data destructor.
        ~ReadData();

};



#endif
