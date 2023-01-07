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
         * Exit the application.
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
         * The promt that is displayed before each user input
        */ 
        const std::string promt {"advisorbot> "};

        /**
         * These are usage messages for the help <cmd> command.
        */
        std::map<std::string, std::string> helpMessages = {
            {"help", promt + "help: Prints this help message."},
            {"prod", promt + "prod: Prints the products that are currently being traded."},
            {"min", promt + "min <product> {ask bid}: Find minimum bid or ask for product in current time step.\n" + promt + "min ETH/BTC ask -> The min ask for ETH/BTC is 1.0"},
            {"max", promt + "max <product> {ask bid}: Find maximum bid or ask for product in current time step.\n" + promt + "max ETH/BTC ask -> The max ask for ETH/BTC is 1.0"},
            {"avg", promt + "avg <product> {ask bid} <timesteps>: Compute average ask or bid price for the product over the specified number of time steps.\n" + promt + "avg ETH/BTC bid 10 -> average of ETH/BTC bid over last 10 time steps."},
            {"predict", promt + "predict {max min} <product> {ask bid} : Predict max or min ask or bid price for the specified product for the next time step.\n" + promt + "predict max ETH/BTC bid -> predicted max bid price for ETH/BTC for the next time step."},
            {"time", promt + "time: Prints the current time."},
            {"step", promt + "step: Move to the next time step."},
            {"back", promt + "back: Move back to the previous time step."},
            {"load", promt + "load <filename>: Load the order book from the specified file."},
            {"volume", promt + "volume <product> {ask bid} <timesteps>: Compute the volume of the specified product over the specified number of time steps.\n" + promt + "volume ETH/BTC bid 10 -> volume of ETH/BTC bid over last 10 time steps."},
            {"exit", promt + "exit: Exit from the chat."}
        };


};
