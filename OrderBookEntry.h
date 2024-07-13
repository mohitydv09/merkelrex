#pragma once
#include <string>

enum class OrderBookType{bid, ask, unknown, bidsale, asksale};

class OrderBookEntry{
public:
    OrderBookEntry( double price,
                    double amount,
                    std::string timestamp,
                    std::string product,
                    OrderBookType orderType,
                    std::string username = "dataset"
                    );

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;

    static OrderBookType string2orderBookType(std::string s);
    static bool compareByTimestamp(OrderBookEntry& order1, OrderBookEntry& order2);
    static bool compareByPriceAscending(OrderBookEntry& order1, OrderBookEntry& order2);
    static bool compareByPriceDescending(OrderBookEntry& order1, OrderBookEntry& order2);
};