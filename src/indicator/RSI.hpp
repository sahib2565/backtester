#pragma once
#include <cstddef>

class RSI{
    private:
        std::size_t period;
        bool hasPrev;
        double prevClose;
        std::size_t count;
        double sumGain, sumLoss;
        double avgGain, avgLoss;
        double lastRsi;
        bool readyFlag;
    public:
        RSI(std::size_t period);
        bool ready() const;
        void update(double close);
        double value() const;
        void reset();
};