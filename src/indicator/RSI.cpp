#include "RSI.hpp"
#include <algorithm>
#include <stdexcept>

// Constructor

RSI::RSI(std::size_t period)
    : period(period),
      hasPrev(false),
      prevClose(0),
      count(0),
      sumGain(0),
      sumLoss(0),
      avgGain(0),
      avgLoss(0),
      lastRsi(0),
      readyFlag(false)
{
    if(period == 0){
        throw std::invalid_argument("Period must be greater than 0");
    }
}

void RSI::reset() {
    hasPrev = false;
    count = 0;
    sumGain = 0;
    sumLoss = 0;
    avgGain = 0; avgLoss = 0;
    readyFlag = false;
    lastRsi = 0;
    prevClose = 0;
}

bool RSI::ready() const {
    return readyFlag;
}

void RSI::update(double close) {
    if(hasPrev == false){
        prevClose = close;
        hasPrev = true;
        return;
    }
    double delta = close - prevClose;
    double gain = std::max(delta,0.0);
    double loss = std::max(-delta,0.0);

    prevClose = close;

    if(readyFlag == false){
        sumGain += gain;
        sumLoss += loss;
        count++;
        if(count == period){
            avgGain = sumGain / period;
            avgLoss = sumLoss / period;
            // Compute last RSI
            if(avgLoss == 0 && avgGain == 0){
                lastRsi = 50;
            }
            else if(avgLoss == 0 && avgGain > 0){
                lastRsi = 100;
            }
            else if(avgGain == 0 && avgLoss > 0){
                lastRsi = 0;
            }else{
                double rs = avgGain / avgLoss;
                lastRsi = 100-(100/(1+rs));
            }
            readyFlag = true;
            return;
        }
    }
    if(readyFlag == true){
        avgGain = (avgGain*(period - 1) + gain) / period;
        avgLoss = (avgLoss*(period - 1) + loss) / period;
        // Compute last RSI
        if(avgLoss == 0 && avgGain == 0){
                lastRsi = 50;
        }
        else if(avgLoss == 0 && avgGain > 0){
            lastRsi = 100;
        }
        else if(avgGain == 0 && avgLoss > 0){
            lastRsi = 0;
        }else{
            double rs = avgGain / avgLoss;
            lastRsi = 100-(100/(1+rs));
        }
    }
}

double RSI::value() const {
    if(!readyFlag){
        throw std::logic_error("RSI not ready");
    }
    return lastRsi;
}