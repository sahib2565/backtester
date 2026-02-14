#include "Broker.hpp"

//Constructor

Broker::Broker(double _slippage, double _commission)
    :_currentState(State::FLAT),
     _entryPrice(0.0),
     _quantity(0.0),
     _commission(_commission),
     _slippage(_slippage)
{};

double Broker::submitOrder(int signal, double currentPrice, double currentQuantity){
    double pnl = 0.0;
    if(_currentState == State::LONG && signal == -1){
        double exitPrice = currentPrice * (1 - _slippage);
        pnl = ((exitPrice*currentQuantity) - (_entryPrice * _quantity)) - (2*_commission);
        // Reset all the values
        _currentState = State::FLAT;
        _entryPrice = 0;
        _quantity = 0;
        return pnl;
    }
    else if(_currentState == State::SHORT && signal == 1){
        double exitPrice = currentPrice * (1 + _slippage);
        pnl = ((_entryPrice*_quantity) - (exitPrice*currentQuantity)) - (2*_commission);
        // Reset values
        _currentState = State::FLAT;
        _entryPrice = 0;
        _quantity = 0;
        return pnl;
    }
    if(_currentState == State::FLAT && signal == -1){
        _currentState = State::SHORT;
        _entryPrice = currentPrice * (1 - _slippage);
        _quantity = currentQuantity;
    }
    else if(_currentState == State::FLAT && signal == 1){
        _currentState = State::LONG;
        _entryPrice = currentPrice * (1 + _slippage);
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

double Broker::getUnrealizedPL(double price) const{
    if(_currentState == State::FLAT){
        return 0.0;
    }
    if(_currentState == State::LONG){
        return (price-_entryPrice) * _quantity;
    }
    if(_currentState == State::SHORT){
        return (_entryPrice-price) * _quantity;
    }
    return 0.0;
}