#include "coordinate.hpp"
#include "../item/item.hpp"

#include <iostream>

#ifndef ENTITY
#define ENTITY
#include "../entity/entity.hpp"
#endif

#ifndef ENEMY
#define ENEMY
#include "../entity/enemy.hpp"
#endif

struct Room
{
    p_itemList itemList;
    int roomTracker; // It track the exaxt room to draw based on the file where resides

    // Four direction, the room point to another linked in the map
    // points to NULL if there is no more rooms in that direction.
    Room *up;
    Room *down;
    Room *left;
    Room *right;
};
typedef Room *p_Room;
class GameEnvironment
{
public:
    GameEnvironment();

    // Menu and static windows printing
    void printMenuLogo();
    void printMenuChoices(int choice);
    void printHowToPlay();
    void escHowToPlay(int key);
    std::string readScoreboard(int n);
    void printScoreboard();
    void escScoreboard(int key);
    void printLoss(int score);
    void escLoss(int key, int score);
    void escWin(int key, int score);
    void printWin(int score);
    void printLore();
    void escLore(int key);
    void save(char saveName[], int score);
    bool nameCheck(char saveName[]);

    // Room and info/stat drawing
    std::string readNthLine(int n);
    void drawRoom(int bottomDistance, int startX, int startY, bool noEnemy, int lineCounter);
    void drawInfo(int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy, Entity entity, int points, int keyCounter, int hearts, p_EnemyList h_enemyList);
    void clearInfo(int rightDistance, int bottomDistance, int startX, int startY);
    void drawActionBox(int rightDistance, int bottomDistance, int startX, int startY, int actionId);
    void cleanActionBox(int rightDistance, int bottomDistance, int startX, int startY);
    p_Room saveRoomState(p_itemList h_itemList, p_Room h_roomList, int roomTracker);
    void openDoorWithKey(Entity entity, int &keyCounter, int rightDistance, int bottomDistance, int startX, int startY, bool noEnemy);
    void openAllDoors(int rightDistance, int bottomDistance, int startX, int startY, int lineCounter);
    void closeAllDoors(bool noEnemy, int rightDistance, int bottomDistance, int startX, int startY);
    p_Room mapGenerator(p_Room h_roomList);
    std::tuple<p_Room, int> roomChange(Entity &entity, p_EnemyList &h_enemyList, p_Room h_roomList, p_itemList h_itemList, int bottomDistance, int rightDistance,
                                       int startX, int startY, bool noEnemy, int points, int enemyCounter, bool passRooms[]);
    // Item and Enemies utilities
    int lenghtItemList(p_itemList h_itemList);
    int lenghtEnemyList(p_EnemyList h_enemyList);
    bool checkItemPosition(p_itemList h_itemList, p_itemList tmpItem);
    void calculateEnemyNumber(int &roomTracker, int &enemyCounter);
    void drawItems(p_itemList h_itemList);
    Position randomCoordinate(int start, int end);
    p_itemList generateItem(int itemCounter, p_itemList h_itemList);
    
    // Player and elements moving
    void moveEnemies(p_EnemyList h_enemyList);
    void drawCharacter(int x, int y, char c);
    void drawEnemies(GameEnvironment gameEnvironment, p_EnemyList h_enemyList);
};
