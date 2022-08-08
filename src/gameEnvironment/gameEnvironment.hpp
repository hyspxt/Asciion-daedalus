#include "coordinate.hpp"

class GameEnvironment {

    public:
    GameEnvironment();
    
    // Menu Printing
    void printMenuLogo();
    void printMenuChoices(int choice);
    void printHowToPlay();
    void escHowToPlay(int key);

    // Room drawing
    void drawRoom(int leftDistance, int bottomDistance, int startX, int startY, bool noEnemy);

    // Player and elements moving
    void drawCharacter(int x, int y, char c);
    
};

struct Room{

    p_Position itemList;

    // Four direction, the room point to another linked in the map
    // points to NULL if there is no more rooms in that direction
    Room *up;
    Room *down;
    Room *left;
    Room *right;
};
typedef Room p_Room;