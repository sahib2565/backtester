#include "Portfolio.hpp"
#include <stdexcept>

// Constructor

Portfolio::Portfolio(double startCapital)
    :_balance(startCapital),
    _initialCapital(startCapital)
{}

void Portfolio::updateBalance(double pnl){
    _balance += pnl;
    return;
}

double Portfolio::getBalance() const{
    return _balance;
}

double Portfolio::getEquity(const Broker& broker, double currentPrice) const{
    double unrealizedPnL = broker.getUnrealizedPL(currentPrice);

    return _balance + unrealizedPnL;
}

double Portfolio::ROI() const{
    return _balance - _initialCapital;
}