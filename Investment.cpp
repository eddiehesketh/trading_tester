#include "Investment.h"

using namespace std;

Investment::Investment(float initial_capital):capital(initial_capital){};

Investment::Investment():Investment(0){};

float Investment::get_capital(){return this->capital;}

void Investment::set_capital(float new_capital){this->capital = new_capital;} 



