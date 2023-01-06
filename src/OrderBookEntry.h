/**
 * This class represents an entry in the order book
*/
#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry
{
    public:
        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string username = "dataset");

        /**
         * Converts a string to an OrderBookType
        */
        static OrderBookType stringToOrderBookType(std::string s);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};
