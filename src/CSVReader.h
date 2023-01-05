#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        static OrderBookEntry stringsToOBE(const std::vector<std::string>& tokens);
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
};
