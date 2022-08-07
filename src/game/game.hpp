#include "../entity/player.hpp"

class Game
{

protected:
    // Represents the distance between the player and the limit (border of room)
    // in the specified direction. Serves for collision checks, etc...
    int leftDistance;
    int rightDistance;
    int topDistance;
    int bottomDistance;

    // These are the starting point for the cursor to draw rooms
    int maxX;
    int maxY;

public:
    Game();
    Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY);

    void ncursesSetup();
    void ncursesStop();
    void movePlayer(Player player);
};