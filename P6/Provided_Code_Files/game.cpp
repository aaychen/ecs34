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
    std::basic_ifstream<char> infile{filename}; // initialize istream to open filename
    std::string buf;
    std::size_t tempIndex = filename.find_last_of("/");
    std::string dirPath = (tempIndex != std::string::npos) ? filename.substr(0, tempIndex+1) : "";
    infile >> screenHeight >> screenWidth;
    infile >> totalLevels;
    for (int i = 0; i < totalLevels; i++) {
        infile >> buf;
        levelFiles.push_back(dirPath + buf);
    }
    
    if (mInterfaceType == InterfaceType::Print) {
        mController = new PrintController();
        if (screenHeight > MIN_VIEW_HEIGHT && screenWidth > MIN_VIEW_WIDTH)
            mView = new PrintView(screenHeight, screenWidth);
        else if (screenHeight > MIN_VIEW_HEIGHT)
            mView = new PrintView(screenHeight, MIN_VIEW_WIDTH);
        else if (screenWidth > MIN_VIEW_WIDTH)
            mView = new PrintView(MIN_VIEW_HEIGHT, screenWidth);
        else 
            mView = new PrintView(MIN_VIEW_HEIGHT, MIN_VIEW_WIDTH);
    } else if (mInterfaceType == InterfaceType::Curses) {
        mController = new CursesController();
        if (screenHeight > MIN_VIEW_HEIGHT && screenWidth > MIN_VIEW_WIDTH)
            mView = new CursesView(screenHeight, screenWidth);
        else if (screenHeight > MIN_VIEW_HEIGHT)
            mView = new CursesView(screenHeight, MIN_VIEW_WIDTH);
        else if (screenWidth > MIN_VIEW_WIDTH)
            mView = new CursesView(MIN_VIEW_HEIGHT, screenWidth);
        else 
            mView = new CursesView(MIN_VIEW_HEIGHT, MIN_VIEW_WIDTH);
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
    bool passLevel = true;
    std::string endMessage;
    Command user_in;
    while (true) {
        if (passLevel) {
            currentLevel++;
            if (currentLevel > totalLevels) {
                endMessage = "You won the game.";
                break;
            }
            loadLevel();
            passLevel = false; // WHEN TO SET TO TRUE?
        }
        std::cout << "Level: " << currentLevel << std::endl;
        std::cout << "Items remaining: " << numItemsRemaining << std::endl;
        std::cout << "Moves remaining: " << numMovesRemaining << std::endl;
        draw();
        user_in = mController->getInput();
        if (user_in == Command::Quit) {
            endMessage = "You quit the game.";
            break;
        }
        update(user_in);
        if (numItemsRemaining == 0) {
            if (currentLevel != totalLevels) {
                passLevel = true;
            } else {
                endMessage = "You won the game.";
                break;
            }
        } else if (numMovesRemaining == 0) {
            endMessage = "You lost the game.";
            break;
        }
    }
    std::cout << endMessage << std::endl;
    return;
}

void Game::loadLevel() {
    mapSegments.clear();
    std::string levelFileName = levelFiles[currentLevel - 1];
    std::basic_ifstream<char> infile{levelFileName}; // initialize istream to open filename
    std::string buf;
    std::string direction; 
    char tempCode;
    int tempMapSegID, tempY, tempX;
    numItemsRemaining = 0;
    infile >> currentMapSegment;
    infile >> playerY >> playerX;
    infile >> direction;
    if (tolower(direction[0]) == 'u') heroIcon = HERO_ICON_UP;
    else if (tolower(direction[0]) == 'd') heroIcon = HERO_ICON_DOWN;
    else if (tolower(direction[0]) == 'l') heroIcon = HERO_ICON_LEFT;
    else heroIcon = HERO_ICON_RIGHT;
    while (infile >> tempCode) {
        if (tempCode == 'M') {
            infile >> tempY >> tempX;
            MapSegment* ms = new MapSegment(tempY, tempX); // create MapSegment object
            mapSegments.push_back(ms);
        } else if (tempCode == 'B') {
            infile >> tempMapSegID >> tempY >> tempX;
            mapSegments[tempMapSegID]->addBuilding(tempY, tempX); // add building to mapSegments[id]
        } else if (tempCode == 'I') {
            infile >> tempMapSegID >> tempY >> tempX;
            mapSegments[tempMapSegID]->addItem(tempY, tempX); // add item to mapSegments[id]
            numItemsRemaining++;
        } else if (tempCode == 'P') {
            // line format: 'P' [seg1_ID] [wall] [seg2_ID] [wall]
            int sourceID, destID;
            std::string sourceWall, destWall;
            infile >> sourceID >> sourceWall >> destID >> destWall;
            mapSegments[sourceID]->addPortal(sourceWall);
            mapSegments[destID]->addPortal(destWall);
        } else if (tempCode == 'N') {
            infile >> numMovesRemaining;
        }
    }
    mapSegments[currentMapSegment]->setPlayerDirection(playerY, playerX, heroIcon);
    return;
}

void Game::draw() {
    std::vector<std::string> msAsLines = mapSegments[currentMapSegment]->getAsLines();
    for (size_t row = 0; row < msAsLines.size(); row++) {
        std::cout << msAsLines[row] << std::endl;
    }
    // mView->draw(msAsLines);
    return;
}

void Game::update(Command move) {
    if (move == Command::Left) { // counter-clockwise rotation
        if (heroIcon == HERO_ICON_UP) heroIcon = HERO_ICON_LEFT;
        else if (heroIcon == HERO_ICON_LEFT) heroIcon = HERO_ICON_DOWN;
        else if (heroIcon == HERO_ICON_DOWN) heroIcon = HERO_ICON_RIGHT;
        else heroIcon = HERO_ICON_UP;
        mapSegments[currentMapSegment]->setPlayerDirection(playerY, playerX, heroIcon);
    }
    else if (move == Command::Right) { // clockwise rotation
        if (heroIcon == HERO_ICON_UP) heroIcon = HERO_ICON_RIGHT;
        else if (heroIcon == HERO_ICON_RIGHT) heroIcon = HERO_ICON_DOWN;
        else if (heroIcon == HERO_ICON_DOWN) heroIcon = HERO_ICON_LEFT;
        else heroIcon = HERO_ICON_UP;
        mapSegments[currentMapSegment]->setPlayerDirection(playerY, playerX, heroIcon);
    }
    else if (move == Command::Forward) {
        if (willCollide()) return;
        if (heroIcon == HERO_ICON_UP) {
            if (mapSegments[currentMapSegment]->movePlayerForward(playerY, playerX, heroIcon, playerY-1, playerX))
                numItemsRemaining--;
            playerY--;
        }
        else if (heroIcon == HERO_ICON_LEFT) {
            if (mapSegments[currentMapSegment]->movePlayerForward(playerY, playerX, heroIcon, playerY, playerX-1))
                numItemsRemaining--;
            playerX--;
        }
        else if (heroIcon == HERO_ICON_DOWN) {
            if (mapSegments[currentMapSegment]->movePlayerForward(playerY, playerX, heroIcon, playerY+1, playerX))
                numItemsRemaining--;
            playerY++;
        }
        else {
            if (mapSegments[currentMapSegment]->movePlayerForward(playerY, playerX, heroIcon, playerY, playerX+1))
                numItemsRemaining--;
            playerX++;
        }
    } else return;
    numMovesRemaining--;
    return;
}

// Collisions against walls and buildings
bool Game::willCollide() {
    int newY = playerY, newX = playerX;
    if (heroIcon == HERO_ICON_UP) { newY--; }
    else if (heroIcon == HERO_ICON_LEFT) { newX--; }
    else if (heroIcon == HERO_ICON_DOWN) { newY++; }
    else { newX++; }

    int msHeight = mapSegments[currentMapSegment]->getHeight();
    int msWidth = mapSegments[currentMapSegment]->getWidth();
    if (newY == 0 || newY == msHeight-1 || newX == 0 || newX == msWidth-1)
        return true;
    std::vector<Building*> buildings = mapSegments[currentMapSegment]->getBuildings();
    for (size_t i = 0; i < buildings.size(); i++) {
        if (buildings[i]->contains(newY, newX))
            return true;
    }
    return false;
}


