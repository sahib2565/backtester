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
    public:
        // Constructor
        Broker();
        double submitOrder(int signal,double currentPrice, double currentQuantity = 1.0);
        // Getter functions for debugging
        State getState() const;
        bool isOpen() const;
};