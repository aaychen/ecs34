#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"
#include "view.hpp"
#include "interface_type.hpp"
#include "map_segment.hpp"

class Game
{
public:  // public methods
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    void run();

private:  // private methods
    /**
     * You DO NOT need to have any of the private methods below.
     * I just left some commented out declarations in case it
     * helps guide your thinking, but you don't need to use them.
     */

    /**
     * Set up the 1D vector of strings that is then given to the draw()
     * method of an instance of a subclass of View.
     */
    void draw();

    /**
     * Loop until the game is over. On each iteration, use the controller
     * to get input from the user.
     */
    // Command doGameLoop();

    /**
     * Update matters related to game logic, e.g. collisions, level completion.
     */
    void update(Command move);

    /**
     * Load information related to new level into member variables,
     * being careful to not leave traces of information from previous levels. 
     */
    void loadLevel();

    /**
     * Checks if the player will collide with portals, walls, or buildings if 
     * they move forward.
     * @return true if there is a collision; false otherwise
     */
    bool willCollide();
    
    /**
     * Specifically checks for portal collisions.
     * @param newY Player's row position in the map segment if move forward
     * @param newX Player's column position in the map segment if move forward
     * @return true if will "collide" with a portal; false otherwise
     */
    bool checkPortalCollision(int newY, int newX);

    /**
     * Finds the connecting destination portal.
     * @param sourceWall The wall that the source portal is located at
     * @return map segment ID and wall location of destination portal
     */
    std::vector<int> findDestinationPortal(int sourceWall);

    /**
     * Updates game such that player has passed through a portal
     * @param destWall wall location of destination portal
     */
    void portalChange(char destWall);

    /**
     * Prints the current level, number of items remaining, and number of 
     * moves remaining.
     */
    void printGameStatus();


private:
    static const int MIN_VIEW_HEIGHT;
    static const int MIN_VIEW_WIDTH;
    static const char HERO_ICON_LEFT;
    static const char HERO_ICON_RIGHT;
    static const char HERO_ICON_UP;
    static const char HERO_ICON_DOWN;

    /**
     * Because one of the constructor parameters must be checked in order
     * to determine the subclass types for the below members, they can't
     * be references, because there's no default constructors for them.
     * (Recall that each member in a class must either be initialized by an
     * initializer list in the constructor OR have a default constructor.)
     */
    View* mView;
    Controller* mController;

    InterfaceType mInterfaceType;

    int screenHeight, screenWidth;
    int totalLevels, currentLevel;
    std::vector<std::string> levelFiles;
    int currentMapSegment;
    std::vector<MapSegment> mapSegments; // mapSegments.size() == totalMapSegments
    int playerX, playerY;
    int numItemsRemaining, numMovesRemaining;
    char heroIcon;
    std::vector<std::vector<int>> portalConnections;

};

#endif // GAME_HPP
