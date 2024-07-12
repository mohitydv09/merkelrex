#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
                    double price,
                    double amount,
                    std::string timestamp,
                    std::string product,
                    OrderBookType orderType)
    : price(price),
        amount(amount),
        timestamp(timestamp),
        product(product),
        orderType(orderType)
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