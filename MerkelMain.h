#pragma once

#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
class MerkelMain
{
public:
    MerkelMain(); // Constructor
    /** Call this to initialize the app. */
    void init();
private:
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void processUserOption(int userOption);

    OrderBook orderbook{"data.csv"};
};