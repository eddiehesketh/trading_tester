#ifndef READDATA_H
#define READDATA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class ReadData{

    protected:
        std::string titles;
        std::string name;
        std::vector<std::string> date;
        std::vector<float> stock_open;
        std::vector<float> stock_close;
        std::vector<float> stock_high;
        std::vector<float> stock_low;
        std::vector<long long> volume;  
        std::ifstream stock_data;


    
    public:

        ReadData(std::string stock_info);
        ReadData();

        std::string clean_value(std::string value);

        std::string clean_money(std::string value);

        std::string clear_commas(std::string volume);

        void process_data();

        void set_titles();

        void set_stock_data(std::string stock_file_name);

        std::ifstream& get_stock_data();

        void set_dates(std::stringstream& ss);
        void set_stock_open(std::stringstream& ss);
        void set_stock_close(std::stringstream& ss);
        void set_stock_high(std::stringstream& ss);
        void set_stock_low(std::stringstream& ss);
        void set_stock_volume(std::stringstream& ss);

        void set_stock_name(std::string name);

        const std::string get_name();

        const std::vector<std::string>& get_dates() const;
        const std::vector<float>& get_open_prices() const;
        const std::vector<float>& get_close_prices() const;
        const std::vector<float>& get_stock_high() const;
        const std::vector<float>& get_stock_low() const;
        const std::vector<long long>& get_volume() const;
    

        virtual void invest_strat(){};

        // ~ReadData();

};



#endif
