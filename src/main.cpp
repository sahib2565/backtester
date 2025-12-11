#include "./market/Candle.hpp"
#include "./market/DataLoader.hpp"
#include "./market/Market.hpp"
#include "./indicator/RSI.hpp"
#include "./indicator/EMA.hpp"
#include <iostream>

int main() {
  std::vector<Candle> data = loadData("./data/EURUSD1440.csv");
  std::cout << data.size() << std::endl;
  Market market(data);
  RSI rsi(14);
  EMA ema(14);

  while (market.next()) {
    double close = market.current().close;
    rsi.update(close);
    ema.update(close);
    std::cout << "Time: " << market.current().timestamp << std::endl;
    std::cout << "Open: " << market.current().open << std::endl;
    std::cout << "Close: " << market.current().close << std::endl;
    std::cout << "Volume: " << market.current().volume << std::endl;
    if(rsi.ready()){
      std::cout << "RSI: " << rsi.value() << std::endl;
    }
    if(ema.ready()){
      std::cout << "EMA: " << ema.value() << std::endl;
    }
    std::cout << "\n";
  }
  return 0;
}
