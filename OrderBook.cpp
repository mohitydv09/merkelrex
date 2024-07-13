#include "OrderBook.h"
#include "CSVReader.h"
#include <map>

OrderBook::OrderBook(std::string filename){
    orders = CSVReader::readCSV(filename);
};

std::vector<std::string> OrderBook::getKnownProducts(){
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& order : orders){
        prodMap[order.product] = true;
    }

    for(auto const& item : prodMap){
        products.push_back(item.first);
    }

    return products;
};

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp){

    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& order : orders){
        if(order.orderType == type && order.product == product && order.timestamp == timestamp){
            orders_sub.push_back(order);
        }
    }
    return orders_sub;
};

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for (OrderBookEntry& order : orders){
        if (order.price < min){
            min = order.price;
        }
    }
    return min;
};

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for (OrderBookEntry& order : orders){
        if (order.price > max){
            max = order.price;
        }
    }
    return max;
};