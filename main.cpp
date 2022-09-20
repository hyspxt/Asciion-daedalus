
#include "src/game/game.hpp"
#include <unistd.h>
#include <string>

#define LEFT_DISTANCE 22
#define RIGHT_DISTANCE 71
#define TOP_DISTANCE 7
#define BOTTOM_DISTANCE 20
#define START_X 7
#define START_Y 22

int main()
{
    Game game(LEFT_DISTANCE, RIGHT_DISTANCE, TOP_DISTANCE, BOTTOM_DISTANCE, START_X, START_Y);
    GameEnvironment gameEnvironment;

    game.ncursesSetup();
    game.choiceHandler(gameEnvironment);
    game.ncursesStop();
    
    return(0);
}