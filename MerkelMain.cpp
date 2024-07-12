#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain(){}

void MerkelMain::init(){
    int input;
    loadOrderBook();
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook(){
    orders = CSVReader::readCSV("data.csv");
}

void MerkelMain::printMenu(){
    std::cout << "1. Print Help" << std::endl;
    std::cout << "2. Print Exchange Stats" << std::endl;
    std::cout << "3. Place a ask" << std::endl;
    std::cout << "4. Place a bid" << std::endl;
    std::cout << "5. Print Wallet" << std::endl;
    std::cout << "6. Continue" << std::endl;
    std::cout << "====================" << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption;
    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    std::cout << std::endl;

    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help: Choose opitons from the menu " << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats(){
    std::cout << "OrderBook Contains: " << orders.size() << " entries." << std::endl;
    int asks = 0;
    int bids = 0;
    for (OrderBookEntry& order : orders){
        if (order.orderType == OrderBookType::ask){
            asks++;
        }else if (order.orderType == OrderBookType::bid){
            bids++;
        }
    }
    std::cout << "Number of Bids: " << bids << std::endl;
    std::cout << "Number of Asks: " << asks << std::endl;
}

void MerkelMain::enterAsk(){
    std::cout << "Enter a ask Price. " << std::endl;
}

void MerkelMain::enterBid(){
    std::cout << "Make a bid. " << std::endl;
}

void MerkelMain::printWallet(){
    std::cout << "Wallet Details : " << std::endl;
}

void MerkelMain::gotoNextTimeframe(){
    std::cout << "Continuing.." << std::endl;
}

void MerkelMain::processUserOption(int userOption){
    switch(userOption){
        case 0:
            std::cout << "Invalid Choice. Choose 1-6 " << std::endl;
            break;
        case 1:
            printHelp();
            break;
        case 2:
            printMarketStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNextTimeframe();
            break;
    }
}
