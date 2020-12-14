#include "building.hpp"

const int Building::width = 6;
const int Building::height = 4;

Building::Building(int y, int x)
    : mY(y), mX(x)
{
}

void Building::drawIn(std::vector<std::string>& board) const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (2 <= i && i <= 3 && 2 <= j && j <= 3)
                board[mY + i][mX + j] = '&';
            else
                board[mY + i][mX + j] = '.';
        }
    }
    return;
}

// useful for checking collisions
bool Building::contains(int y, int x) const {
    if (mY <= y && y < mY + height 
                && mX <= x && x < mX + width) {
        return true;
    }
    return false;
}
