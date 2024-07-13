#include "Wallet.h"
#include "CSVReader.h"


Wallet::Wallet(){};


void Wallet::insertCurrency(std::string type, double amount){
    double balance;
    if (amount < 0){
        throw std::exception{};
    }
    if (currencies.count(type) == 0){
        balance = 0;
    }else{
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
};

bool Wallet::removeCurrency(std::string type, double amount){
    double balance;
    if (amount < 0){
        throw std::exception{};
    }
    if (currencies.count(type) == 0){
        return false;
    }else{
        balance = currencies[type];
    }
    balance -= amount;
    if (balance < 0){
        return false;
    }
    currencies[type] = balance;
    return true;
};

bool Wallet::containsCurrency(std::string type, double amount){
    if (currencies.count(type) == 0){
        return false;
    }else{
        return currencies[type] >= amount;
    }
};

std::string Wallet::toString(){
    std::string s = "Wallet Contents: \n";
    for (const std::pair<std::string, double>& pair : currencies){
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
};

bool Wallet::canFulfillOrder(OrderBookEntry order){
    std::vector<std::string> currs = CSVReader::tokenise(order.product,'/');
    //Ask Condition.
    if (order.orderType == OrderBookType::ask){
        double amount = order.amount;
        std::string currency = currs[0];
        return containsCurrency(currency, amount);
    }
    //Bid
    if (order.orderType == OrderBookType::bid){
        double amount = order.amount;
        std::string currency = currs[1];
        return containsCurrency(currency, amount);
    }
    return false;
};

void Wallet::processSale(OrderBookEntry& sale){
    std::vector<std::string> currs = CSVReader::tokenise(sale.product,'/');
    //Ask Condition.
    if (sale.orderType == OrderBookType::asksale){
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    //Bid
    if (sale.orderType == OrderBookType::bidsale){
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
};

std::ostream& operator<<(std::ostream& os, Wallet& wallet){
    os << wallet.toString();
    return os;
}