#include "Investment.h"
#include "Portfolio.h"
#include <iostream>

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

