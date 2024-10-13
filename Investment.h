#ifndef INVESTMENT_H
#define INVESTMENT_H
#include "ReadData.h"


class Investment: public ReadData{

    protected:
        float capital;
        float invest_return;
        float deposit_amount;
        int index;
        float final_capital;
        float profits;
        std::string start_date_;

        std::string investment_type;

        // float dividend_yield;
        float widthdrawn_cash;
        std::string pay_freq;
        bool reinvest_status;

        // Momentum
        int period;
        int momentum;
        std::vector<double> signals; 
        double meanPrice;

        // MovingAverageCrossover
        int Period1;
        int Period2;
        int shortPeriod;
        int longPeriod;
        int shares;
        float invested_capital;
        bool isInvested;

    public:

        Investment(float initial_capital, std::string stock_info_);
        virtual ~Investment() = default;

        // Investment();

        virtual void investment_stratergy() = 0;

        float get_capital();

        void set_capital(float new_capital);

        virtual bool valid_start_date(std::string _start_date);

        void set_index(int _index);

        void set_final_capital(int _capital);

        float get_final_capital();

        void set_profits(float _profits);

        void set_start_date(std::string _start_date);

        int get_index();

        virtual bool valid_pay_freq(std::string freq) = 0;

        void set_reivest_status(bool stat);

        void set_pay_freq(std::string freq);

        std::string get_pay_freq();

        void set_widthdrawn_cash(float v);

        float get_widthdrawn_cash();

        float get_profits();

        virtual void set_investment_type() = 0;

        std::string get_investment_type();

        virtual double calcMomentum(int period, int index_val);
        
        virtual void detectMomentum();

        int capitalToShares(double capital, double closePrice);

        double sharesToCapital(int shares, double closePrice);

        virtual void finalizeSimulation(); 

        virtual void largePeriod(int period1, int period2);
        
        virtual double MovingAverage(int period, int currentIndex);

        virtual void detectCrossover();

        bool get_reinvest_status();



        
};

#endif

    // void detectCrossover();