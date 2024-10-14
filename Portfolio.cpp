// Including the relevant libraries.
#include "Investment.h"
#include "Portfolio.h"
#include <iostream>
#include <fstream> // For file management.
#include <ostream> // For outputting files.

// Using the standard namespace.
using  namespace std;


// Portfolio constructor, initialises portfolio value to zero, capacity to six and count to zero.
Portfolio::Portfolio(): portfolio_value(0.0), capacity(6), count(0){

    // Creates an array of investment pointers, of size capacity.
    this->investments = new Investment*[capacity];

}

// Add investment in, taking in an investment pointer.
void Portfolio::add_investment(Investment* _investment){

    // Checks if the count is less than six.
    if (get_count() < 6){

        // Sets the index at count to the new investment pointer.
        investments[count] = _investment;

        // Increases count by one.
        count++;
        
        // Sets new portfolio value.
        set_portfolio_value();

    } else {

        // Inform user that investments are full.
        cout << "Investments full" << endl;
    }

}

// Remove investment function.
void Portfolio::remove_investment(int index){

    // Checks if the index is greater than zero and less than count.
    if (index >=0 && index < count){

        // If so, that index investment is deleted.
        delete investments[index];

        // Loop iterating from index to count - 1, shifting all investments back one index.
        for (int i = index; i < count - 1; i++){
            // Shifting all investments left.
            investments[i] = investments[i+1];
        }

        // Sets final index to a nullptr.
        investments[get_count()-1] = nullptr;

        // Decreases count by one.
        set_count(get_count()-1);
    }

    // Set new portfolio value.
    set_portfolio_value();

}

// Set portfolio value function.
void Portfolio::set_portfolio_value(){

    // Sets a running total capital variable to zero.
    float total_capital = 0;

    // Iterates over all investments and adds their capital to the running capital variable.
    for (int i = 0; i < count; i++){

        // Adding each final capital to the total capital variable.
        total_capital = total_capital + investments[i]->get_final_capital();
    }

    // Sets the porfolio value to the total capital variable.
    this->portfolio_value = total_capital;
}

// Getter function to return count.
int Portfolio::get_count(){return this->count;}

// Setter function to set the count.
void Portfolio::set_count(int c){this->count = c;}

// Getter function to get the portfolio value.
float Portfolio::get_portfolio_value(){return this->portfolio_value;}

// Destructor for portfolio class
Portfolio::~Portfolio(){

    // Iterate over each element and delete the memeory allocated to it.
    for (int i = 0; i < count; i++){

        // Delete each investment.
        delete investments[i];
    }

    // Delete the double pointer.
    delete[] investments;
}

// Write portfolio summary function.
void Portfolio::write_portfolio_summary(){

    // Create and open an output file stream to write the summary to a file named investment_summary.txt
    ofstream output_file("investment_summary.txt");

    // Check if the file is successfully opened for writing.
    if (output_file.is_open()){

        // Write the header of the portfolio summary.
        output_file << "Investment portfolio summary\n\n";

        // Loop through all the investments in the portfolio.
        for (int i = 0; i < get_count(); i++){

            // Write information about each investment.
            output_file << "Investment " << i+1 << ": " << investments[i]->get_investment_type() << "\n"; // Investment type.
            output_file << "    Company name: " << investments[i]->get_name() << "\n"; // Company name.
            output_file << "    Start date: " << investments[i]->get_start_date() << "\n"; // Start date.
            output_file << "    Initial capital: $" << investments[i]->get_capital() << "\n"; // Initial capital.
            output_file << "    Final capital: $" << investments[i]->get_final_capital() << "\n"; // Final capital.
            output_file << "    Profits: $" << investments[i]->get_profits() << "\n"; // Profits.
            output_file << "\n\n";
        }

        // Closing statement.
        output_file << "Total portfolio value: $" << get_portfolio_value() << "\n";
        output_file.close();

    }


}

// Get Investment function
Investment* Portfolio::get_investment(int index) {
    if (index >= 0 && index < count) {
        return investments[index];
    }
    return nullptr;  // Return null if index is out of bounds
}
