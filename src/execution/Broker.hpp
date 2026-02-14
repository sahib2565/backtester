#pragma once
enum class State{
    FLAT,
    LONG,
    SHORT
};

class Broker{
    private:
        State _currentState;
        double _entryPrice;
        double _quantity;
        double _commission;
        double _slippage; // Slippage is a percentage of the price
    public:
        // Constructor
        Broker(double _slippage, double _commission);
        double submitOrder(int signal,double currentPrice, double currentQuantity = 1.0);
        // Getter functions for debugging
        State getState() const;
        bool isOpen() const;
        double getUnrealizedPL(double price) const;
};