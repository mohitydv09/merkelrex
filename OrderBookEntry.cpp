#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
                    double price,
                    double amount,
                    std::string timestamp,
                    std::string product,
                    OrderBookType orderType,
                    std::string username)
    : price(price),
        amount(amount),
        timestamp(timestamp),
        product(product),
        orderType(orderType),
        username(username)
{};

OrderBookType OrderBookEntry::string2orderBookType(std::string s){
    if (s == "ask"){
        return OrderBookType::ask;
    }else if(s == "bid"){
        return OrderBookType::bid;
    }else{
        return OrderBookType::unknown;
    }
};

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& order1, OrderBookEntry& order2){
    return order1.timestamp < order2.timestamp;
};

bool OrderBookEntry::compareByPriceAscending(OrderBookEntry& order1, OrderBookEntry& order2){
    return order1.price < order2.price;
};

bool OrderBookEntry::compareByPriceDescending(OrderBookEntry& order1, OrderBookEntry& order2){
    return order1.price > order2.price;
};