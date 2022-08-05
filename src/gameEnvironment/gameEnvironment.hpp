#include "coordinate.hpp"
#include "../entity/enemy.hpp"

class GameEnvironment {

    public:
    GameEnvironment();
    
    // Menu Printing
    void printMenuLogo();
    void printMenuChoices(int choice);
    void printHowToPlay();
    void escHowToPlay(int key);
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