#include "building.hpp"

const int Building::width = 6;
const int Building::height = 4;

Building::Building(int y, int x)
    : mY(y), mX(x)
{
}

// useful for checking collisions
bool Building::contains(int y, int x) const {
    if (mY >= y && mY <= y + height)
        if (mX >= x && mX <= x + width)
            return true;
    return false;
}
