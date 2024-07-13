#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

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

double OrderBook::meanPrice(std::vector<OrderBookEntry>& orders){
    double sum_ = 0;
    for (const OrderBookEntry& order : orders){
        sum_ += order.price;
    }
    return sum_/orders.size();
};

std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
};

std::string OrderBook::getNextTime(std::string timestamp){
    std::string nextTimestamp = "";
    for (OrderBookEntry& order : orders){
        if(order.timestamp > timestamp){
            nextTimestamp = order.timestamp;
            break;
        }
    }
    if (nextTimestamp == ""){
        nextTimestamp = orders[0].timestamp;
    }
    return nextTimestamp;
};

void OrderBook::insertOrder(OrderBookEntry& order){
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
};

std::vector<OrderBookEntry> OrderBook::matchAskstoBids(std::string product, std::string timestamp){
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                    product,
                                                    timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                    product,
                                                    timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAscending);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDescending);

    for (OrderBookEntry& ask : asks){
        for (OrderBookEntry& bid : bids){
            if (bid.price >= ask.price){

                OrderBookEntry sale{ask.price,
                                    0,
                                    timestamp,
                                    product,
                                    OrderBookType::asksale};

                OrderBookType type = OrderBookType::asksale;
                if (bid.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;;
                }
                if (ask.username == "simuser"){
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                if (bid.amount == ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                }
                if (bid.amount > ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
};