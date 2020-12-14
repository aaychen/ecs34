#include "map_segment.hpp"

#include <iostream> // testing purposes

char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width)
    : mHeight(height), mWidth(width)
    , mPortalY{(mHeight - 1) / 2}
    , mPortalX{(mWidth - 1) / 2}
{
    msAsLines = std::vector<std::string>(mHeight);
    for (int row = 0; row < mHeight; row++) {
        msAsLines[row] = std::string(mWidth, ' ');
        for (int col = 0; col < mWidth; col++) {
            if (row == 0 || row == mHeight-1) {
                msAsLines[row][col] = HORIZONTAL_BORDER_CHAR;
            } else if (col == 0 || col == mWidth-1) {
                msAsLines[row][col] = VERTICAL_BORDER_CHAR;
            }
        }
    }
}

// destructor
MapSegment::~MapSegment() {
    // for (size_t i = 0; i < buildingsVector.size(); i++) {
    //     delete buildingsVector[i];
    // }
    // for (size_t i = 0; i < itemsVector.size(); i++) {
    //     delete itemsVector[i];
    // }
}

std::vector<std::string> MapSegment::getAsLines() const {
    return msAsLines;
}

void MapSegment::addBuilding(int y, int x) {
    Building* b = new Building(y, x);
    b->drawIn(msAsLines);
    buildingsVector.push_back(b);
    return;
}

std::vector<Building*> MapSegment::getBuildings() {
    return buildingsVector;
}

void MapSegment::addItem(int y, int x) {
    Item* i = new Item(y, x);
    i->drawIn(msAsLines);
    itemsVector.push_back(i);
    return;
}

void MapSegment::addPortal(std::string wall) {
    if (tolower(wall[0]) == 'r') {
        msAsLines[mPortalY][mWidth-1] = PORTAL_CHAR;
    } else if (tolower(wall[0]) == 'l') {
        msAsLines[mPortalY][0] = PORTAL_CHAR;
    } else if (tolower(wall[0]) == 'd') {
        msAsLines[mHeight-1][mPortalX] = PORTAL_CHAR;
    } else if (tolower(wall[0]) == 'u') {
        msAsLines[0][mPortalX] = PORTAL_CHAR;
    }
    return;
}

void MapSegment::setPlayerDirection(int yPos, int xPos, char heroIcon) {
    msAsLines[yPos][xPos] = heroIcon;
    return;
}

bool MapSegment::movePlayerForward(int oldY, int oldX, char heroIcon, int newY, int newX) {
    bool foundItem = false;
    msAsLines[oldY][oldX] = ' ';
    if (msAsLines[newY][newX] == '$') 
        foundItem = true;
    msAsLines[newY][newX] = heroIcon;
    return foundItem;
}
