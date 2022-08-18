#include "coordinate.hpp"
#include "../item/item.hpp"


#ifndef ENTITY
#define ENTITY
#include "../entity/entity.hpp"
#endif

#ifndef ENEMY
#define ENEMY
#include "../entity/enemy.hpp"
#endif

class GameEnvironment
{

public:
    GameEnvironment();

    // Menu Printing
    void printMenuLogo();
    void printMenuChoices(int choice);
    void printHowToPlay();
    void escHowToPlay(int key);
    void printScoreboard();
    void escScoreboard(int key);
    void printLoss(int score);
    void escLoss(int key, int score);
    void save(char saveName[], int score);
    bool nameCheck(char saveName[]);

    // Room drawing
    void drawRoom(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy);
    void drawInfo(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy, Entity entity, int points);

    // Player and elements moving
    void drawCharacter(int x, int y, char c);

    void drawEnemies(GameEnvironment gameEnvironment, p_EnemyList h_enemyList);
};

struct Room
{

    p_itemList itemList;
    int roomTracker; // It track the exaxt room to draw based on the file where resides

    // Four direction, the room point to another linked in the map
    // points to NULL if there is no more rooms in that direction
    Room *up;
    Room *down;
    Room *left;
    Room *right;
};
typedef Room p_Room;