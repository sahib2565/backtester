#include "Broker.hpp"

//Constructor

Broker::Broker()
    :_currentState(State::FLAT),
     _entryPrice(0.0),
     _quantity(0.0)
{};

double Broker::submitOrder(int signal, double currentPrice, double currentQuantity){
    double pnl = 0.0;
    if(_currentState == State::LONG && signal == -1){
        pnl = (currentPrice*currentQuantity) - (_entryPrice * _quantity);
        // Reset all the values
        _currentState = State::FLAT;
        _entryPrice = 0;
        _quantity = 0;
        return pnl;
    }
    else if(_currentState == State::SHORT && signal == 1){
        pnl = (_entryPrice*_quantity) - (currentPrice*currentQuantity);
        // Reset values
        _currentState = State::FLAT;
        _entryPrice = 0;
        _quantity = 0;
        return pnl;
    }
    if(_currentState == State::FLAT && signal == -1){
        _currentState = State::SHORT;
        _entryPrice = currentPrice;
        _quantity = currentQuantity;
    }
    else if(_currentState == State::FLAT && signal == 1){
        _currentState = State::LONG;
        _entryPrice = currentPrice;
        _quantity = currentQuantity;
    }
    return 0.0;
}

State Broker::getState() const {
    return _currentState;
}

bool Broker::isOpen() const {
    if(_currentState != State::FLAT){
        return true;
    }else{
        return false;
    }
}