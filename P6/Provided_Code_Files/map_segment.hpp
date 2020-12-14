#ifndef MAP_SEGMENT_HPP
#define MAP_SEGMENT_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "item.hpp"

/**
 * This is probably the class that will have the second biggest portion of
 * your code for this assignment. (The biggest would likely be held
 * by the Game class.)
 *
 * Some things I did that you don't have to do:
 * - Define an enum class for portal directions.
 * - Method for connecting two map segments' portals.
 * - Methods for adding buildings or items to a map segment.
 */

class MapSegment
{
public:

    MapSegment(int height, int width);

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    int getPortalX() const { return mPortalX; }
    int getPortalY() const { return mPortalY; }

    /**
     * Returns representation of this map segment as a vector of strings,
     * including any contained items and buildings.
     */
    std::vector<std::string> getAsLines() const;

    ~MapSegment();
    void addBuilding(int y, int x);
    std::vector<Building> getBuildings();
    void addItem(int y, int x);
    void addPortal(std::string wall);
    void setPlayerDirection(int yPos, int xPos, char heroIcon);
    bool movePlayerForward(int oldY, int oldX, char heroIcon, int newY, int newX);
    void removePlayer(int yPos, int xPos);
    // void enterPortal(char wall, char heroIcon);

private:
    static char VERTICAL_BORDER_CHAR;
    static char HORIZONTAL_BORDER_CHAR;
    static char PORTAL_CHAR;

    /**
     * As always, you don't need to have these member variables if you don't
     * think they would be useful to you.
     */

    int mHeight;
    int mWidth;
    /**
     * For helping position the portals.
     * See how they are initialized in the constructor.
     */
    int mPortalY;
    int mPortalX;

    std::vector<std::string> msAsLines;
    std::vector<Building> buildingsVector;
    std::vector<Item> itemsVector;

};

#endif // MAP_SEGMENT_HPP
