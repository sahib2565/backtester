#pragma once
#include "../execution/Broker.hpp" // Necessario per interagire col broker

class Portfolio {
private:
    double _balance;        // I soldi liquidi (Cash)
    double _initialCapital; // Con quanto siamo partiti (utile per statistiche future)

public:
    // Costruttore: Setta il capitale iniziale
    Portfolio(double startCapital);

    // Chiamato SOLO quando un trade viene CHIUSO.
    // Aggiunge (o sottrae) il PnL al balance.
    void updateBalance(double pnl); 

    // Restituisce il Balance attuale (senza posizioni aperte)
    double getBalance() const;

    // Calcola: Balance + Profitto non realizzato del Broker
    // Ha bisogno del broker e del prezzo attuale per fare i conti
    double getEquity(const Broker& broker, double currentPrice) const;

    //Get return on investment

    double ROI() const;
};