#include "map_segment.hpp"

char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width)
    : mHeight(height), mWidth(width)
    , mPortalY{(mHeight - 1) / 2}
    , mPortalX{(mWidth - 1) / 2}
{
}

// destructor
MapSegment::~MapSegment() {
    for (size_t i = 0; i < buildings.size(); i++) {
        delete buildings[i];
    }
    for (size_t i = 0; i < items.size(); i++) {
        delete items[i];
    }
}

void MapSegment::addBuilding(int y, int x) {
    Building* b = new Building(y, x);
    buildings.push_back(b);
    return;
}

std::vector<Building*> MapSegment::getBuildings() {
    return buildings;
}

void MapSegment::addItem(int y, int x) {
    Item* i = new Item(y, x);
    items.push_back(i);
    return;
}

std::vector<Item*> MapSegment::getItems() {
    return items;
}

