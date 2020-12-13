#include "game.hpp"
#include "curses_view.hpp"
#include "curses_controller.hpp"
#include "print_view.hpp"
#include "print_controller.hpp"

#include <iostream>
#include <fstream>

// NOTE: NO INPUT VALIDATION REQUIRED
// These should not have been here in the first place... 
// #define INVALID_GAME_FILE_MSG "Invalid game input file"
// #define INVALID_LEVEL_FILE_MSG "Invalid level input file"
// #define INVALID_VIEW_TYPE_MSG "Invalid view type"

const int Game::MIN_VIEW_HEIGHT = 15;
const int Game::MIN_VIEW_WIDTH = 15;
const char Game::HERO_ICON_LEFT = '<';
const char Game::HERO_ICON_RIGHT = '>';
const char Game::HERO_ICON_UP = '^';
const char Game::HERO_ICON_DOWN = 'v';

Game::Game(const std::string& filename, InterfaceType interfaceType)
    : mView{nullptr}
    , mController{nullptr}
    , mInterfaceType{interfaceType}
{
    // TODO: Implement.
    if (mInterfaceType == InterfaceType::Print) {
        mController = new PrintController();
        mView = new PrintView(Game::MIN_VIEW_HEIGHT, Game::MIN_VIEW_WIDTH);
    } else if (mInterfaceType == InterfaceType::Curses) {
        mController = new CursesController();
        mView = new CursesView(Game::MIN_VIEW_HEIGHT, Game::MIN_VIEW_WIDTH);
    }

    std::basic_ifstream<char> infile{filename}; // initialize istream to open filename
    std::string buf;
    // getline(infile, buf);
    // sscanf(buf.c_str(), " %d %d ", &screenHeight, &screenWidth);
    // getline(infile, buf);
    // sscanf(buf.c_str(), " %d ", &totalLevels);

    // std::string testFileName = "game1.txt";
    // std::size_t tempIndex = testFileName.find_last_of("/");
    // std::string dirPath = (tempIndex != std::string::npos) ? testFileName.substr(0, tempIndex+1) : "";
    // std::cout << dirPath << std::endl;
    std::size_t tempIndex = filename.find_last_of("/");
    std::string dirPath = (tempIndex != std::string::npos) ? filename.substr(0, tempIndex+1) : "";
    int i = 1;
    while (getline(infile, buf)) {
        if (i == 1) sscanf(buf.c_str(), " %d %d ", &screenHeight, &screenWidth);
        else if (i == 2) sscanf(buf.c_str(), " %d ", &totalLevels);
        else levelFiles.push_back(dirPath + buf);
        i++;
    }
    currentLevel = 0;
}

Game::~Game()
{
    // TODO: Usually, deallocate anything that was dynamically
    // allocated in the ctor (constructor).
    delete mController;
    delete mView;
    for (size_t i = 0; i < mapSegments.size(); i++) {
        // mapSegments[i]->~MapSegment();
        delete mapSegments[i];
    }
}

void Game::run()
{
    // TODO: Implement.

    // Check level file names
    // for (int i = 0; i < levelFiles.size(); i++) {
    //     std::cout << levelFiles[i] << std::endl;
    // }

    bool passLevel = true;
    std::string endMessage;
    Command user_in;
    while (true) {
        // user_in = doGameLoop();
        if (passLevel) {
            currentLevel++;
            if (currentLevel > totalLevels) {
                endMessage = "You won the game.";
                break;
            }
            loadLevel();
            passLevel = false; // WHEN TO SET TO TRUE?
        }
        user_in = mController->getInput();
        if (user_in == Command::Quit) {
            endMessage = "You quit the game.";
            break;
        }
        update(user_in);
    }
    std::cout << endMessage << std::endl;
    return;
}

void Game::loadLevel() {
    std::string levelFileName = levelFiles[currentLevel - 1];
    std::basic_ifstream<char> infile{levelFileName}; // initialize istream to open filename
    std::string buf;
    // getline(infile, buf);
    // sscanf(buf.c_str(), " %d ", &currentMapSegment);
    // getline(infile, buf);
    // sscanf(buf.c_str(), " %d %d ", &playerY, &playerX);
    // getline(infile, buf);
    char direction;
    // sscanf(buf.c_str(), " %c", &direction);
    // direction = tolower(direction);
    // if (direction == 'u') heroIcon = Game::HERO_ICON_UP;
    // else if (direction == 'd') heroIcon = Game::HERO_ICON_DOWN;
    // else if (direction == 'l') heroIcon = Game::HERO_ICON_LEFT;
    // else heroIcon = Game::HERO_ICON_RIGHT;
    // std::cout << buf << std::endl;
    // std::cout << direction << std::endl;
    // std::cout << heroIcon << std::endl;
    char tempCode;
    int tempMapSegID, tempY, tempX;
    int i = 1;
    while (getline(infile, buf)) {
        std::cout << buf << std::endl;
        if (i == 1) sscanf(buf.c_str(), " %d ", &currentMapSegment);
        else if (i == 2) sscanf(buf.c_str(), " %d %d ", &playerY, &playerX);
        else if (i == 3) {
            sscanf(buf.c_str(), " %c", &direction);
            direction = tolower(direction);
            if (direction == 'u') heroIcon = Game::HERO_ICON_UP;
            else if (direction == 'd') heroIcon = Game::HERO_ICON_DOWN;
            else if (direction == 'l') heroIcon = Game::HERO_ICON_LEFT;
            else heroIcon = Game::HERO_ICON_RIGHT;
        }
        else {
            if (buf[0] == 'M') {
                sscanf(buf.c_str(), " %c %d %d ", &tempCode, &tempY, &tempX);
                MapSegment* ms = new MapSegment(tempY, tempX); // create MapSegment object
                mapSegments.push_back(ms);
            } else if (buf[0] == 'B') {
                sscanf(buf.c_str(), " %c %d %d %d ", &tempCode, &tempMapSegID, &tempY, &tempX);
                mapSegments[tempMapSegID]->addBuilding(tempY, tempX); // add building to mapSegments[id]
            } else if (buf[0] == 'I') {
                sscanf(buf.c_str(), " %c %d %d %d ", &tempCode, &tempMapSegID, &tempY, &tempX);
                mapSegments[tempMapSegID]->addItem(tempY, tempX); // add item to mapSegments[id]
                totalItems++;
            } else if (buf[0] == 'P') {

            } else if (buf[0] == 'N') {
                sscanf(buf.c_str(), " %c %d ", &tempCode, &maxMoves);
            }
        }
        i++;
    }
    std::cout << "currentMapSegment: " << currentMapSegment << std::endl;
    std::cout << "(playerY, playerX): " << "(" << playerY << ", " << playerX << ")" << std::endl;
    std::cout << "cursor: " << heroIcon << std::endl;
    for (size_t i = 0; i < mapSegments.size(); i++) {
        std::cout << "mapSegments[" << i << "]: " << mapSegments[i]->getHeight() << " " << mapSegments[i]->getWidth() << std::endl;
        std::cout << "numBuildings: " << mapSegments[i]->getBuildings().size() << std::endl;
        std::cout << "numItems: " << mapSegments[i]->getItems().size() << std::endl;
    }
    std::cout << "maxMoves: " << maxMoves << std::endl;
    numItemsFound = 0;
    numMovesPlayed = 0;
    return;
}

// Command Game::doGameLoop() {
//     return mController->getInput();
// }

void Game::update(Command move) {
    if (move == Command::Left) { // counter-clockwise rotation
        if (heroIcon == Game::HERO_ICON_UP)
            heroIcon = Game::HERO_ICON_LEFT;
        else if (heroIcon == Game::HERO_ICON_LEFT)
            heroIcon = Game::HERO_ICON_DOWN;
        else if (heroIcon == Game::HERO_ICON_DOWN)
            heroIcon = Game::HERO_ICON_RIGHT;
        else
            heroIcon = Game::HERO_ICON_UP;
    }
    else if (move == Command::Right) { // clockwise rotation
        if (heroIcon == Game::HERO_ICON_UP)
            heroIcon = Game::HERO_ICON_RIGHT;
        else if (heroIcon == Game::HERO_ICON_RIGHT)
            heroIcon = Game::HERO_ICON_DOWN;
        else if (heroIcon == Game::HERO_ICON_DOWN)
            heroIcon = Game::HERO_ICON_LEFT;
        else
            heroIcon = Game::HERO_ICON_UP;
    }
    else if (move == Command::Forward) {
        if (heroIcon == Game::HERO_ICON_UP)
            playerY--;
        else if (heroIcon == Game::HERO_ICON_LEFT)
            playerX--;
        else if (heroIcon == Game::HERO_ICON_DOWN)
            playerY++;
        else
            playerX++;
    }
    std::cout << heroIcon << "\n";
    return;
}

void checkCollision() {
    return;
}


