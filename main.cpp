#include "src/gameEnvironment/gameEnvironment.hpp"
#include <unistd.h>

int main()
{
    // Put here game class and window drawing
    GameEnvironment gameEnvironment;
    gameEnvironment.printMenuLogo();
    for (int i = 0; i < 5; i++)
    {
        gameEnvironment.printMenuChoices(i);
        sleep(1);
    }
    gameEnvironment.printHowToPlay();

    return (0);
}