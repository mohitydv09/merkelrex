#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

double computeAveragePrice(std::vector<OrderBookEntry>& entries){
    double totalPrice = 0;
    for (OrderBookEntry& entry : entries){
        totalPrice += entry.price;
    }
    return totalPrice/entries.size();
}

double computeLowPrice(std::vector<OrderBookEntry>& entries){
    double lowPrice = __DBL_MAX__;
    for (OrderBookEntry& entry : entries){
        if (entry.price < lowPrice){
            lowPrice = entry.price;
        }
    }
    return lowPrice;
}

double computeHighPrice(std::vector<OrderBookEntry>& entries){
    double highPrice = __DBL_MIN__;
    for (OrderBookEntry& entry : entries){
        if (entry.price > highPrice){
            highPrice = entry.price;
        }
    }
    return highPrice;
}

double computePriceSpread(std::vector<OrderBookEntry>& entries){
    double lowPrice = computeLowPrice(entries);
    double highPrice = computeHighPrice(entries);
    return highPrice-lowPrice;
}


int main()  {
    MerkelMain app;
    app.init();
}