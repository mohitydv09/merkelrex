#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>

MerkelMain::MerkelMain(){}

void MerkelMain::init(){
    int input;
    currentTime = orderbook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu(){
    std::cout << "1. Print Help" << std::endl;
    std::cout << "2. Print Exchange Stats" << std::endl;
    std::cout << "3. Place a ask" << std::endl;
    std::cout << "4. Place a bid" << std::endl;
    std::cout << "5. Print Wallet" << std::endl;
    std::cout << "6. Continue" << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << "Current Time is: " << currentTime << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption;
    std::string line = "";
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);

    try{
        userOption = std::stoi(line);
        std::cout << "You chose: " << userOption << std::endl;
    }catch(std::exception& e){
        std::cout << "Input number from 1-6" << std::endl;
    }
    std::cout << std::endl;

    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help: Choose opitons from the menu " << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStats(){

    std::cout << "Below is the list of products in orders." << std::endl;

    for (std::string const& prod : orderbook.getKnownProducts()){
        std::cout << "Product: " << prod << std::endl;
        std::vector<OrderBookEntry> entries = orderbook.getOrders(OrderBookType::ask, prod, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        // std::cout << "Max Ask Price: " << orderbook.getHighPrice(entries) << std::endl;
        // std::cout << "Min Ask Price: " << orderbook.getLowPrice(entries) << std::endl;
        std::cout << "Mean Price: " << orderbook.meanPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk(){
    std::cout << "Make a ask, Enter the amount: product, price, amount (eg ETH/BTC, 200, 0.55)" << std::endl;
    std::string user_input;

    // Clear the cin buffer.
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );

    std::getline(std::cin, user_input);
    std::vector<std::string> tokens = CSVReader::tokenise(user_input, ',');
    if(tokens.size() != 3){
        std::cout << "Bad Input: " << user_input << std::endl;
    }else{
        try{
            OrderBookEntry obe = CSVReader::strings2OrderBookEntry(tokens[1],
                                                                    tokens[2],
                                                                    currentTime,
                                                                    tokens[0],
                                                                    OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)){
                std::cout << "Wallet Looks good. " << std::endl;
                orderbook.insertOrder(obe);
            }else{
                std::cout << "Insufficient funds. " << std::endl;
            }
            
        }catch (const std::exception& e){
            std::cout << "MerkelMain::enterAsk, Bad Input: " << std::endl;
        }

    }
    std::cout << "You entered: " << user_input << std::endl;
}

void MerkelMain::enterBid(){
    std::cout << "Make a Bid, Enter the amount: product, price, amount (eg ETH/BTC, 200, 0.55)" << std::endl;
    std::string user_input;

    std::getline(std::cin, user_input);
    std::vector<std::string> tokens = CSVReader::tokenise(user_input, ',');
    if(tokens.size() != 3){
        std::cout << "Bad Input: " << user_input << std::endl;
    }else{
        try{
            OrderBookEntry obe = CSVReader::strings2OrderBookEntry(tokens[1],
                                                                    tokens[2],
                                                                    currentTime,
                                                                    tokens[0],
                                                                    OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe)){
                std::cout << "Wallet Looks good. " << std::endl;
                orderbook.insertOrder(obe);
            }else{
                std::cout << "Insufficient funds. " << std::endl;
            }
            
        }catch (const std::exception& e){
            std::cout << "MerkelMain::enterBid, Bad Input: " << std::endl;
        }

    }
    std::cout << "You entered: " << user_input << std::endl;
}

void MerkelMain::printWallet(){
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe(){
    std::cout << "Going to next time Frame." << std::endl;
    
    for (std::string prod : orderbook.getKnownProducts()){
        std::cout << "Matching: " << prod << std::endl;
        std::vector<OrderBookEntry> sales = orderbook.matchAskstoBids(prod, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales){
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser"){
                //username
                wallet.processSale(sale);
            }
        }
    }


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
