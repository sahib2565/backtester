#include "DataLoader.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

uint64_t toEpochMs(const std::string& dt){
    tm tm = {};
    std::istringstream ss(dt);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    time_t timeSec = timegm(&tm);
    return (uint64_t)timeSec * 1000;
}

std::vector<Candle> loadData(const std::string& filename){
    std::ifstream file(filename);
    std::string line;

    std::vector<Candle> data;
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string dateTime, open, high, low, close, volume;

        std::getline(ss,dateTime, '\t');
        std::getline(ss, open,'\t');
        std::getline(ss, high,'\t');
        std::getline(ss, low,'\t');
        std::getline(ss, close,'\t');
        std::getline(ss, volume, '\t');

        data.push_back({
            toEpochMs(dateTime),
            stod(open),
            stod(high),
            stod(low),
            stod(close),
            stod(volume)
        });
    }

    return data;
}