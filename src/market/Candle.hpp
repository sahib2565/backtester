#pragma once
#include <cstdint>

struct Candle {
    uint64_t timestamp; //epoch time (ms or sec)
    double open;
    double high;
    double low;
    double close;
    double volume;
};