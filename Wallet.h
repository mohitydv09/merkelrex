#pragma once

#include <string>
#include <map>

#include "OrderBookEntry.h"

class Wallet{
public:
    Wallet();
    /**Insert currency in wallet */
    void insertCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);
    bool containsCurrency(std::string type, double amount);
    /**Get string rep of the string. */
    std::string toString();
    friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    /**Checks if the wallet can cope with the order. */
    bool canFulfillOrder(OrderBookEntry order);

    void processSale(OrderBookEntry& sale);

private:
    std::map<std::string, double> currencies;

};