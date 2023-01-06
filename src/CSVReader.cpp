#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

/**
 * This code is based on the original CSVReader::readCSV() function provided in the course.
 * It has been modified to use std::move() to avoid copying.
 *
 * This function reads a CSV file and returns a vector of OrderBookEntry objects.
 *
 * @param csvFilename The name of the file to read
 * @return A vector of OrderBookEntry objects
*/
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

/**
 * This code is based on the original CSVReader::stringsToOBE() function provided in the course.
 *
 * This function converts a vector of strings into an OrderBookEntry object.
 *
 * @param tokens A vector of strings containing the data to be converted
 * @return An OrderBookEntry object
*/
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

/**
 * This code is based on the original CSVReader::tokenise() function provided in the course.
 * It has been modified to use const references and to use std::move() to avoid copying.
 * 
 * This function tokenises (splits) a string into a vector of strings by the specified separator
 *
 * @param csvLine The line to be tokenised
 * @param separator The character to use as a separator
 * @return A vector of strings containing the tokens
*/
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
