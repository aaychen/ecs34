#include "item.hpp"

char Item::ICON = '$';

Item::Item(int y, int x)
    : mY(y), mX(x)
{
}

void Item::drawIn(std::vector<std::string>& board) const {
    board[mY][mX] = ICON;
    return;
}
