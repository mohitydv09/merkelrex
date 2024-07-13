#pragma once

#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
class MerkelMain
{
public:
    MerkelMain(); // Constructor
    /** Call this to initialize the app. */
    void init();
    std::string currentTime;
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

    Wallet wallet;
};