#include "ReadData.h"
#include "Display.h"
#include <iostream>

using namespace std;


Display::Display(std::string stock): ReadData(stock){};



string Display::single_open_prices(int day) const {


// debugging - check if openPrices is empty
    auto openPrices = get_open_prices();
    if (openPrices.empty()) {
        std::cerr << "Error: open prices data is empty for stock." << std::endl;
        return "$0.00";  // Or any default value
    }

    float price1 = get_open_prices()[get_open_prices().size()-day];


    string price = to_string(price1);

    price.erase(price.find_first_of(".")+3);

    price.insert(0, "$");

    return price;

}

string Display::single_close_prices(int day) const {

    float price1 = get_close_prices()[get_close_prices().size()-day];

    string price = to_string(price1);

    price.erase(price.find_first_of(".")+3);

    price.insert(0, "$");

    return price;

}

string Display::single_dates(int day) const {

    return get_dates()[get_dates().size()-day];

}

string Display::single_volumes(int day) const {

    float volume = get_volume()[get_volume().size()-day];


    string str_vol = to_string(volume);

    str_vol.erase(str_vol.find_first_of("."));

    str_vol.insert(0, "$");

    return str_vol;

}

string Display::daily_change(int day) const {

    float change = 0;
    const vector<float>& open = get_open_prices();
    const vector<float>& close = get_close_prices();
    int index = open.size() - day;
    string return_value = "";

    change = ((close[index] - open[index]) / open[index]) * 100;

    return_value = to_string(change);


    if (close[index] >= open[index]){

        return clean_daily_change(true, return_value);

    } else if (close[index] < open[index]){

        return clean_daily_change(false, return_value);

    }

    return NULL;


}

string Display::clean_daily_change(bool status, string value) const {

    if (status){

        value.insert(0, "+");

        value.erase(value.find_first_of(".")+3);

        value.append("%");

        return value;

    } else if (!status){

        // value.insert(0, "-");

        value.erase(value.find_first_of(".")+3);

        value.append("%");

        return value;
    }

    return NULL;
}

