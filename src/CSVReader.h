/**
 * This class contains functions to read a CSV file and convert it into a vector of OrderBookEntry objects.
*/

#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();
        /**
         * This function reads a CSV file and returns a vector of OrderBookEntry objects.
         *
         * @param csvFilename The name of the file to read
         * @return A vector of OrderBookEntry objects
        */
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);

        /**
         * This function converts a vector of strings into an OrderBookEntry object.
         *
         * @param tokens A vector of strings containing the data to be converted
         * @return An OrderBookEntry object
        */
        static OrderBookEntry stringsToOBE(const std::vector<std::string>& tokens);

        /**
         * This function tokenises (splits) a string into a vector of strings by the specified separator
         *
         * @param csvLine The line to be tokenised
         * @param separator The character to use as a separator
         * @return A vector of strings containing the tokens
        */
        static std::vector<std::string> tokenise(const std::string& csvLine, char separator);
};
