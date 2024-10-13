#include "Investment.h"
#include "Portfolio.h"
#include <iostream>
#include <fstream>
#include <ostream>
using  namespace std;

Portfolio::Portfolio(): portfolio_value(0.0), capacity(6), count(0){

    this->investments = new Investment*[capacity];

}

void Portfolio::add_investment(Investment* _investment){

    if (get_count() < 6){
        investments[count] = _investment;
        count++;

        set_portfolio_value();
    } else {
        cout << "Investments full" << endl;
    }

}

void Portfolio::remove_investment(int index){
    if (index >=0 && index < count){
        delete investments[index];

        for (int i = index; i < count - 1; i++){
            investments[i] = investments[i+1];
        }

        investments[get_count()-1] = nullptr;

        set_count(get_count()-1);
    }

    set_portfolio_value();

}

void Portfolio::set_portfolio_value(){

    float total_capital = 0;

    for (int i = 0; i < count; i++){
        total_capital = total_capital + investments[i]->get_final_capital();
    }

    this->portfolio_value = total_capital;
}


int Portfolio::get_count(){return this->count;}

void Portfolio::set_count(int c){this->count = c;}

float Portfolio::get_portfolio_value(){return this->portfolio_value;}

Portfolio::~Portfolio(){
    for (int i = 0; i < count; i++){
        delete investments[i];
    }

    delete[] investments;
}

void Portfolio::write_portfolio_summary(){

    ofstream output_file("investment_summary.txt");

    if (output_file.is_open()){

        output_file << "Investment portfolio summary\n\n";

        for (int i = 0; i < get_count(); i++){
            output_file << "Investment " << i+1 << ": " << investments[i]->get_investment_type() << "\n";
            output_file << "    Company name: " << investments[i]->get_name() << "\n";
            output_file << "    Start date: " << investments[i]->get_start_date() << "\n";
            output_file << "    Initial capital: $" << investments[i]->get_capital() << "\n";
            output_file << "    Final capital: $" << investments[i]->get_final_capital() << "\n";
            output_file << "    Profits: $" << investments[i]->get_profits() << "\n";
            output_file << "\n\n";
        }

        output_file << "Total portfolio value: $" << get_portfolio_value() << "\n";
        output_file.close();

    }


}