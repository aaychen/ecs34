#include "curses_controller.hpp"

#include <curses.h>

CursesController::~CursesController()
{
}

Command CursesController::getInput()
{
    // TODO: Implement.
    // Don't forget about the arrow keys.

    char user_in = getch();
    if (user_in == 27 && (user_in = getch()) == '[') { // arrow keys
        user_in = getch();
        if (user_in == 'A')
            return Command::Forward;
        else if (user_in == 'D')
            return Command::Left;
        else if (user_in == 'C')
            return Command::Right;
    }
    else if (user_in == 'w')
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
