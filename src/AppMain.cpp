#include "AppMain.h"
#include <iostream>
#include <vector>
#include <numeric>

#include "CommandProcessor.h"

AppMain::AppMain()
{
}

/**
 * Starts the application
 */
void AppMain::start()
{
    // Set the precision of the float values displayed in the console
    std::cout.precision(floatPrecision);

    // These commands run automatically when the application starts
    CommandProcessor commandProcessor{};
    commandProcessor.help();
    commandProcessor.load({"20200601.csv"});

    // String to store the user input
    std::string input;
    while(true)
    {
        input = readUserInput();

        // Ctrl+D pressed
        if (std::cin.eof())
        {
            // It counts as an exit command
            std::cout << "exit" << std::endl;
            commandProcessor.terminate();
        }

        // Execute the command entered by the user
        commandProcessor.execute(input);
    }
}

/** 
 * Reads user input from the console
 * @return The user input
 */
std::string AppMain::readUserInput()
{
    std::string line;
    std::cout << "user> ";
    std::getline(std::cin, line);

    return line;
}
