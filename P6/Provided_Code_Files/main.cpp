#include "game.hpp"
#include "interface_type.hpp"

int main(int argc, char *argv[])
{
    InterfaceType it = InterfaceType::Print;
    if (argc >= 2) it = InterfaceType::Curses;
    Game g{"../Example_Game_Files/demo_game1.txt", it};
    // Game g{"../Autograder/game_files/game11.txt", it};
    g.run();
}
