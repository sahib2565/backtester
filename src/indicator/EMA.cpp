#include "EMA.hpp"
#include <stdexcept>

// Constructor

EMA::EMA(std::size_t period)
    :period(period),
     lastEma(0),
     readyFlag(false),
     count(0),
     smoothing_factor(2.0/(period+1.0)),
     sumCloses(0)
{
    if(period == 0){
        throw std::invalid_argument("Period can not be 0");
    }
}

void EMA::reset(){
    lastEma = 0;
    readyFlag = false;
    count = 0; sumCloses = 0;
}

bool EMA::ready() const {
    return readyFlag;
}

void EMA::update(double close){
    if(!readyFlag){
        sumCloses += close;
        count++;
        if(count == period){
            lastEma = sumCloses / period;
            readyFlag = true;
        }
    }else{
        lastEma = (smoothing_factor*close) + (1-smoothing_factor) * lastEma;
    }
}

double EMA::value() const{
    if(!readyFlag){
        throw std::logic_error("EMA value is not ready");
    }
    return lastEma;
}