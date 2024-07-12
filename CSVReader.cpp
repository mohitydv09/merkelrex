#include "CSVReader.h"
// #include "OrderBookEntry.h"
#include <iostream>
#include <fstream>
// #include <string>
// #include <vector>


CSVReader::CSVReader(){}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){
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

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName){
    std::vector<OrderBookEntry> data;
    std::vector<std::string> tokens;

    std::ifstream csvFile{csvFileName};
    std::string line;
    
    if (csvFile.is_open()){
        std::cout << "File Opened Successfully" << std::endl;

        while(std::getline(csvFile, line)){
            try{
                tokens = tokenise(line, ',');
                OrderBookEntry obe = strings2OrderBookEntry(tokens);
                data.push_back(obe);
            }catch(const std::exception& e){
                std::cout << "Bad Data. " << std::endl;
            }
        }
        csvFile.close();
    }else{
        std::cout << "File opening failed " << std::endl;
    }
    return data;
};

OrderBookEntry CSVReader::strings2OrderBookEntry(std::vector<std::string> tokens){
    double price;
    double amount;
    if (tokens.size() != 5){
        std::cout << "Bad Data: " << std::endl;
        throw std::exception{};
    }else{
        try{
            price = std::stod(tokens[3]);
            amount = std::stod(tokens[4]);
        } catch(const std::exception& e){
            std::cout << "Bad Value: "<< std::endl;
            throw;
        }
    }
    OrderBookEntry obe{price,
                    amount,
                    tokens[0],
                    tokens[1],
                    OrderBookEntry::string2orderBookType(tokens[2])
    };
    return obe;
};
