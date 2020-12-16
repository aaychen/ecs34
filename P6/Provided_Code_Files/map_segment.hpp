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

    // int getViewY() const { return viewY; }
    // int getViewX() const { return viewX; }

    /**
     * Returns representation of this map segment as a vector of strings,
     * including any contained items and buildings.
     */
    std::vector<std::string> getAsLines() const;

    /**
     * Adds a building at coordinates (y,x) on this map segment.
     */
    void addBuilding(int y, int x);

    /**
     * Returns a list of buildings that are on this map segment.
     */
    std::vector<Building> getBuildings();

    /**
     * Adds an item at coordinates (y,x) on this map segment.
     */
    void addItem(int y, int x);

    /**
     * Adds a portal at the specified wall location.
     */
    void addPortal(std::string wall);

    /**
     * Changes player direction at coordinates (yPos,xPos)
     * @param heroIcon Player's new orientation
     */
    void setPlayerDirection(int yPos, int xPos, char heroIcon);

    /**
     * Moves player forward and collects item if there is any.
     * @param oldY Old row position of player
     * @param oldX Old column position of player
     * @param heroIcon Player's orientation
     * @param newY Row position of player if move forward
     * @param newX Column position of player if move forward
     * @return true if player has reached an item; false otherwise
     */
    bool movePlayerForward(int oldY, int oldX, char heroIcon, int newY, int newX);

    /**
     * Removes player from coordinates (y,x). Used when updating player position on 
     * this map segment.
     */
    void removePlayer(int yPos, int xPos);

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

    /**
     * Lines representation of map segment
     */
    std::vector<std::string> msAsLines;

    std::vector<Building> buildingsVector;

};

#endif // MAP_SEGMENT_HPP
