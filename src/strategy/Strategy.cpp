#include "Strategy.hpp"
#include <stdexcept>

// Constructor

Strategy::Strategy(std::size_t rsiPeriod, std::size_t slowPeriod, std::size_t fastPeriod)
    :inTrade(false),
    emaFast(EMA(fastPeriod)),
    emaSlow(EMA(slowPeriod)),
    rsi(RSI(rsiPeriod)),
    lastRSI(0),
    hasLastRsi(0)
{
    if(fastPeriod == 0 || slowPeriod == 0 || rsiPeriod == 0){
        throw std::invalid_argument("Period must be greater than 0");
    }
}

int Strategy::update(double close){
    rsi.update(close);
    emaFast.update(close);
    emaSlow.update(close);
    if(!rsi.ready()){
        return 0;
    }else{
        if(!inAtrade){
            if(emaFast.value() > emaSlow.value() && lastRSI  < 30 && rsi.value() >= 30){
                inTrade = true;
                return 1;
            }
            if(rsi.value() > 70 || emaFast.value() < emaSlow.value()){
                inTrade = false;
                return -1;
            }
        }
        lastRSI = rsi.value();
    }
}

bool Strategy::inAtrade() const {
    return inTrade;
}