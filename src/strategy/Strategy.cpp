#include "Strategy.hpp"
#include <locale>
#include <stdexcept>

// Constructor

Strategy::Strategy(std::size_t rsiPeriod, std::size_t fastPeriod,
                   std::size_t slowPeriod)
    : inTrade(false), rsi(rsiPeriod), emaFast(fastPeriod), emaSlow(slowPeriod),
      lastRSI(0.0), hasLastRsi(false)

{
  if (fastPeriod == 0 || slowPeriod == 0 || rsiPeriod == 0) {
    throw std::invalid_argument("Period must be greater than 0");
  }
}

int Strategy::update(double close) {
  // 1. Update indicators
  rsi.update(close);
  emaFast.update(close);
  emaSlow.update(close);

  int signal = 0;

  // 2. Warmup handling: if any indicator isn't ready yet
  if (!rsi.ready() || !emaFast.ready() || !emaSlow.ready()) {
    // If RSI is ready, keep track of previous RSI for future crossings
    if (rsi.ready()) {
      lastRSI = rsi.value();
      hasLastRsi = true;
    }
    return 0; // no trading while warming up
  }

  // 3. All indicators are ready: get current values
  double currentRsi = rsi.value();
  double fast = emaFast.value();
  double slow = emaSlow.value();

  // 4. Entry / exit logic
  if (!inTrade) {
    // Entry: uptrend (fast>slow) and RSI crosses back above 30
    if (fast > slow && currentRsi < 30.0) {
      inTrade = true;
      signal = 1; // BUY
    }
  } else { // inTrade == true
    // Exit: RSI overbought or trend breaks
    if (currentRsi > 70.0 || fast < slow) {
      inTrade = false;
      signal = -1; // SELL
    }
  }

  // 5. Store RSI for next tick's crossing logic
  lastRSI = currentRsi;
  hasLastRsi = true;

  return signal;
}

bool Strategy::inAtrade() const { return inTrade; }
