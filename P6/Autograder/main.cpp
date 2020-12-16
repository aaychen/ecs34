#include "game.hpp"
#include "interface_type.hpp"

int main(int argc, char *argv[])
{
    InterfaceType it = InterfaceType::Print;
    std::string gameFile{argv[1]};
    Game g{gameFile, it};
    g.run();
}
