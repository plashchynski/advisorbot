#pragma once

#include <vector>
#include <string>

#include "OrderBook.h"

class CommandProcessor
{
    public:
        CommandProcessor();

        /**
         * Prints the help message.
        */
        void help();

        /**
         * Exit the program.
        */
        void terminate();

        /**
         * Parse user input and execute a command if it is valid.
        */
        void execute(std::string userInput);

    private:
        std::string currentTime;
	    OrderBook orderBook;

        /**
         * Print the usage information for a specific command
         */
        void help(const std::vector<std::string>& args);

        /**
         * Print the products that are currently being traded.
         */
        void prod();

        /**
         * Find minimum bid or ask for product in current time step.
        */
        void min(const std::vector<std::string>& args);

        /**
         * Find maximum bid or ask for product in current time step.
        */
        void max(const std::vector<std::string>& args);

        /**
         * Predict max or min ask or bid price for the specified product for the next time step.
        */
        void predict(const std::vector<std::string>& args);

        /**
         * Compute average ask or bid price for the product over the specified number of time steps.
        */
        void avg(const std::vector<std::string>& args);

        /**
         * Move to the next time step.
        */
        void step();

        /**
         * Print the current time.
        */
        void time();
};
