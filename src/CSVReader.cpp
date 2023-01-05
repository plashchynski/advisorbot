#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    if (!csvFile.is_open())
    {
        std::cout << "CSVReader::readCSV failed to open the file " << csvFilename << std::endl;
        return entries;
    }

    std::string line;
    while(std::getline(csvFile, line))
    {
        try {
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(std::move(obe));
        } catch(const std::exception& e)
        {
            std::cout << "CSVReader::readCSV bad data"  << std::endl;
        }
    }

    return entries;
}

OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens)
{
    double price, amount;

    if (tokens.size() != 5)
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }

    try
    {
         price = std::stod(tokens[3]);
         amount = std::stod(tokens[4]);
    } catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl;
        throw;
    }

    return OrderBookEntry {
        price,
        amount,
        tokens[0],
        tokens[1],
        OrderBookEntry::stringToOrderBookType(tokens[2])
    };
}

std::vector<std::string> CSVReader::tokenise(const std::string &csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(std::move(token));
        start = end + 1;
    } while (end > 0);

   return tokens;
}
