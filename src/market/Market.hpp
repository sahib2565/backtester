#pragma once
#include "Candle.hpp"
#include <vector>
#include <cstddef>

class Market{
    private:
        const std::vector<Candle> &data;
        size_t index;
        bool started;
    public:
        Market(const std::vector<Candle> &data);
        bool next();
        const Candle& current() const;
        const Candle& previous() const;
};