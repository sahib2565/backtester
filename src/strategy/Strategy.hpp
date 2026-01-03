#pragma once
#include "../indicator/EMA.hpp"
#include "../indicator/RSI.hpp"
#include <cstddef>

/*
So the plan is that we will update strategy directly every single candle, so we are going to initialize indicators over there
rather than doing it on the main file
*/

class Strategy{
    private:
        bool inTrade;
        RSI rsi;
        EMA emaFast;
        EMA emaSlow;
        double lastRSI;
        bool hasLastRsi;
    public:
        Strategy(std::size_t rsiPeriod, std::size_t fastPeriod, std::size_t slowPeriod);
        int update(double close); // Return 0 if no trade, return 1 if buy, return -1 if sell
        bool inAtrade() const;
};