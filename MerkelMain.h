#pragma once

#include<vector>
#include "OrderBookEntry.h"
class MerkelMain
{
public:
    MerkelMain(); // Constructor
    /** Call this to initialize the app. */
    void init();
private:
    void printMenu();
    void loadOrderBook();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void processUserOption(int userOption);

    std::vector<OrderBookEntry> orders;
};