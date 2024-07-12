#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "OrderBookEntry.h"

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

std::vector<std::string> tokenise(std::string csvLine, char separator){
    // Implement the funtion
    std::vector<std::string> tokens;

    int start;
    int end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);

    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) {
            break;
        }
        if (end >= 0){
            token = csvLine.substr(start, end-start);
        }else{
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    }while(end != std::string::npos);
    return tokens;
};

int main(){
    std::vector<OrderBookEntry> data;
    std::vector<std::string> tokens;

    std::ifstream csvFile{"1XejnIsmSmK3o5yLJkpiUg_2402656ae54246e880715f135341f5f7_20200317.csv"};
    std::string line;
    
    if (csvFile.is_open()){
        std::cout << "File Opened Successfully" << std::endl;

        while(std::getline(csvFile, line)){
            tokens = tokenise(line, ',');
            if (tokens.size() != 5){
                std::cout << "Bad Data: "<< line << std::endl;
                continue;
            }else{
                try{
                    double price = std::stod(tokens[3]);
                    double amount = std::stod(tokens[4]);
                    OrderBookType orderType;
                    if (tokens[2] == "ask"){
                        orderType = OrderBookType::ask;
                    }else{
                        orderType = OrderBookType::bid;
                    }
                    data.push_back(OrderBookEntry{
                                            price,
                                            amount,
                                            tokens[0],
                                            tokens[1],
                                            orderType
                    });
                    // std::cout << price << " " << amount << std::endl;
                } catch(std::exception& e){
                    std::cout << "Bad Value: "<< std::endl;
                    for (std::string& token : tokens){
                        std::cout << token << std::endl;
                    }
                    continue;
                }
            }
        }
        csvFile.close();
    }else{
        std::cout << "File opening failed " << std::endl;
    }
    double averagePrice = computeAveragePrice(data);
    double lowPrice = computeLowPrice(data);
    double highPrice = computeHighPrice(data);
    double priceSpread = computePriceSpread(data);

    std::cout << "Average Price of data is: " << averagePrice << std::endl;
    std::cout << "Low Price of data is: " << lowPrice << std::endl;
    std::cout << "High Price of data is: " << highPrice << std::endl;
    std::cout << "Spread of Price of data is: " << priceSpread << std::endl;
 

    return 0;
}
