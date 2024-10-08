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
    } else {
        cout << "Investments full" << endl;
    }

}

void Portfolio::remove_investment(int index){
    if (index >=0 && index < count){
        delete investments[index];

        for (int i = index-1; i < count; i++){
            investments[i] = investments[i+1];
        }

        // delete investments[]
    }

    // for 
}


int Portfolio::get_count(){return this->count;}