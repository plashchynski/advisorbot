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

    // open the file
    std::ifstream csvFile{csvFilename};
    if (!csvFile.is_open())
        throw std::runtime_error{"Failed to open the file " + csvFilename};

    // read the file line by line
    std::string line;
    long unsigned int lineCount = 0;
    while(std::getline(csvFile, line))
    {
        lineCount++;
        try
        {
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(std::move(obe)); // std::move() is used to avoid copying
        } catch(const std::exception& e)
        {
            throw std::runtime_error{"Error on line " + std::to_string(lineCount) + " of file " + csvFilename + ": " + e.what()};
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
        throw std::runtime_error{"Wrong number of tokens"};

    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error{"Bad format of floating point number"};
    }

    // Enable mandatory elision of copy as a Return value optimization (RVO) by
    // using prvalue as an operand of return statement
    // More info: https://en.cppreference.com/w/cpp/language/copy_elision
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

        // std::move() is used to avoid copying
        tokens.push_back(std::move(token));
        start = end + 1;
    } while (end > 0);

   return tokens;
}
