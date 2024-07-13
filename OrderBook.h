#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>

class OrderBook{
public:
    /** construct, reading a csv data file. */
    OrderBook(std::string filename);
    /**return , list of known products.*/
    std::vector<std::string> getKnownProducts();
    /**return, the list of Orders with given products at given timestamp. */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

    std::string getEarliestTime();
    std::string getNextTime(std::string timestamp);

    std::vector<OrderBookEntry> matchAskstoBids(std::string product, std::string timestamp);

    //these are static as they don't use the data stored in the class, i.e. orders.
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double meanPrice(std::vector<OrderBookEntry>& orders);

    void insertOrder(OrderBookEntry& order);

private:
    std::vector<OrderBookEntry> orders;
};