/**
 * This class is responsible for parsing user input and executing the actual task.
 *
 * It has the execute method which is called by the AppMain class with the user input as an argument.
 * The execute method make basic validation of the user input, splits the input into tokens,
 * uses the first token to determine the command and calls the appropriate method to execute the command.
 *
 * Each command has its own method which is responsible for validation command arguments and executing the actual task.
*/
#pragma once

#include <vector>
#include <string>
#include <map>

#include "OrderBook.h"

class CommandProcessor
{
    public:
        CommandProcessor();

        /**
         * Parse user input and execute a command if it is valid.
        */
        void execute(std::string userInput);


        // These are commands that can be called directly from outside the class:
        /**
         * Prints the help message.
        */
        void help();

        /**
         * Exit the program.
        */
        void terminate();

        /**
         * Load the order book from the specified file.
        */
        void load(const std::vector<std::string>& args);

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
         * Compute the volume of the specified product over the specified number of time steps.
        */
        void volume(const std::vector<std::string>& args);

        /**
         * Move to the next time step.
        */
        void step();

        /**
         * Move back to the previous time step.
        */
        void back();

        /**
         * Print the current time.
        */
        void time();

        /**
         * These are usage messages for the help <cmd> command.
        */
        std::map<std::string, std::string> helpMessages = {
            {"help", "advisorbot> help: Prints this help message."},
            {"prod", "advisorbot> prod: Prints the products that are currently being traded."},
            {"min", "advisorbot> min <product> {ask bid}: Find minimum bid or ask for product in current time step.\nadvisorbot> min ETH/BTC ask -> The min ask for ETH/BTC is 1.0"},
            {"max", "advisorbot> max <product> {ask bid}: Find maximum bid or ask for product in current time step.\nadvisorbot> max ETH/BTC ask -> The max ask for ETH/BTC is 1.0"},
            {"avg", "advisorbot> avg <product> {ask bid} <timesteps>: Compute average ask or bid price for the product over the specified number of time steps.\nadvisorbot> avg ETH/BTC bid 10 -> average of ETH/BTC bid over last 10 time steps."},
            {"predict", "advisorbot> predict {max min} <product> {ask bid} : Predict max or min ask or bid price for the specified product for the next time step.\nadvisorbot> predict max ETH/BTC bid -> predicted max bid price for ETH/BTC for the next time step."},
            {"time", "advisorbot> time: Prints the current time."},
            {"step", "advisorbot> step: Move to the next time step."},
            {"back", "advisorbot> back: Move back to the previous time step."},
            {"load", "advisorbot> load <filename>: Load the order book from the specified file."},
            {"volume", "advisorbot> volume <product> {ask bid} <timesteps>: Compute the volume of the specified product over the specified number of time steps.\nadvisorbot> volume ETH/BTC bid 10 -> volume of ETH/BTC bid over last 10 time steps."},
            {"exit", "advisorbot> exit: Exit from the chat."}
        };
};
