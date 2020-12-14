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

    bool willCollide();

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
    std::vector<MapSegment*> mapSegments; // mapSegments.size() == totalMapSegments
    int playerX, playerY;
    int numItemsRemaining, numMovesRemaining;
    char heroIcon;

    // Level specific information (need to reset each time when loading a level)
    // currentMapSegment, mapSegments, playerX, playerY, numItemsRemaining, numMovesRemaining, heroIcon

};

#endif // GAME_HPP
