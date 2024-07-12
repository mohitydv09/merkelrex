#pragma once
#include <string>

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry{
public:
    OrderBookEntry( double price,
                    double amount,
                    std::string timestamp,
                    std::string product,
                    OrderBookType orderType
                    );

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    static OrderBookType string2orderBookType(std::string s);
};