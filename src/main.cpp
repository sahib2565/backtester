#include "./market/Candle.hpp"
#include "./market/DataLoader.hpp"
#include "./market/Market.hpp"
#include <iostream>

int main() {
  std::vector<Candle> data = loadData("./data/EURUSD1440.csv");
  std::cout << data.size() << std::endl;
  Market market(data);

  while (market.next()) {
    std::cout << "Time: " << market.current().timestamp << std::endl;
    std::cout << "Open: " << market.current().open << std::endl;
    std::cout << "Close: " << market.current().close << std::endl;
    std::cout << "Volume: " << market.current().volume << std::endl;
    std::cout << "\n";
  }
  return 0;
}
