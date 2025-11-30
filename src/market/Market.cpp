#include "Market.hpp"
#include <cassert>

// Constructor
Market::Market(const std::vector<Candle> &data)
    : data(data), index(0), started(false)
{
}

bool Market::next() {
    if (data.empty()) {
        return false;
    }

    if (!started) {
        started = true;
        index = 0;
        return true;
    }

    if (index + 1 < data.size()) {
        ++index;
        return true;
    }

    return false;
}

const Candle& Market::current() const {
    assert(started && "Market::current() called before first next()");
    assert(index < data.size() && "Market::current() index out of range");
    return data[index];
}

const Candle& Market::previous() const {
    assert(started && "Market::previous() called before first next()");
    assert(index < data.size() && "Market::previous() index out of range");

    if (index > 0) {
        return data[index - 1];
    }
    return data[index]; // at index 0, no previous -> return current by design
}
