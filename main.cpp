
#include "src/game/game.hpp"
#include <unistd.h>
#include <string>


int main()
{
    // Put here game class and window drawing
    Game game(22, 71, 7, 20, 7, 22);
    GameEnvironment gameEnvironment;

    game.ncursesSetup();

    // game.ncursesSetup();
    /* gameEnvironment.drawRoom(71, 20, 7, 22, true);
    gameEnvironment.drawCharacter(30, 19, 'c');

    Weapon weapon("Test", 30);
    Player player(30, 19, 'c', 75, weapon);
    
    game.movePlayer(player);
    */
    game.choiceHandler(gameEnvironment);

    game.ncursesStop();
    
    return(0);
}