#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
                        double _price,
                        double _amount,
                        std::string _timestamp,
                        std::string _product,
                        OrderBookType _orderType,
                        std::string _username
                        ):  price(_price),
                            amount(_amount),
                            timestamp(_timestamp),
                            product(_product),
                            orderType(_orderType),
                            username(_username)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string string)
{
    if (string == "ask")
    {
        return OrderBookType::ask;
    }

    if (string == "bid")
    {
        return OrderBookType::bid;
    }

    return OrderBookType::unknown;
}
