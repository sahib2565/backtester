#pragma once
#include <cstddef>

class EMA{
    private:
        std::size_t period;
        double lastEma;
        bool readyFlag;
        std::size_t count; // Counting how many closes we iterated 
        double smoothing_factor;
        double sumCloses;

    public:
        EMA(std::size_t period);
        bool ready() const;
        void update(double close);
        void reset();
        double value() const;
};