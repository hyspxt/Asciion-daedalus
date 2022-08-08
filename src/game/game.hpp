#include "../entity/player.hpp"
#include "../gameEnvironment/gameEnvironment.hpp"

class Game
{

protected:
    // Represents the distance and the limit (border of room)
    // in the specified direction. Serves for collision checks, etc...
    int leftDistance;
    int rightDistance;
    int topDistance;
    int bottomDistance;

    // These are high leftcornerX low righcornerY
    int maxX;
    int maxY;

    // Pause the game execution
    bool pause;

public:
    Game();
    Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY);

    void ncursesSetup();
    void ncursesStop();

    void movePlayer(Player player);

    void menuChoice(GameEnvironment gameEnvironment, int *key, int *selection);
    void choiceHandler(GameEnvironment gameEnvironment);
};