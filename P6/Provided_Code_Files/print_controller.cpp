#include "print_controller.hpp"

#include <iostream>

PrintController::~PrintController()
{
}

Command PrintController::getInput()
{
    // TODO: Implement.
    char user_in;
    std::cout << "Enter input: ";
    std::cin >> user_in;
    if (user_in == 'w')
        return Command::Forward;
    else if (user_in == 'a')
        return Command::Left;
    else if (user_in == 'd')
        return Command::Right;
    else if (user_in == 'q')
        return Command::Quit;
    return Command::Invalid;
    
    // To prevent a compiler error in the starter files...
    // return Command::Invalid;
}
