#pragma once
#include "Candle.hpp"
#include <vector>
#include <string>
#include <cstdint>

uint64_t toEpochMs(const std::string& dt);
std::vector<Candle> loadData(const std::string& filename);