#include "../gameEnvironment/gameEnvironment.hpp"

#ifndef ENEMY
#define ENEMY
#include "../entity/enemy.hpp"
#endif

#ifndef PLAYER
#define PLAYER
#include "../entity/player.hpp"
#endif
class Game
{

protected:
    // Represents the distance and the limit (border of room)
    // in the specified direction. Serves for collision checks, etc...
    int leftDistance;
    int rightDistance;
    int topDistance;
    int bottomDistance;

    // These are left-up cornerX right-low cornerY
    int maxX;
    int maxY;

    // Pause the game execution -> loss/win
    bool pause;

    int timer;      // Determines the length of various in-game events
    int enemyTimer; // Serves as a clock to make enemies shoot bullets

    p_bullet playerBullets;
    p_bullet enemyBullets;

public:
    // Builder
    Game();
    Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY);

    // Ncurses
    void ncursesSetup();
    void ncursesStop();

    // Inputs
    std::tuple<Entity, int> gameInputs(GameEnvironment gameEnvironment, Entity entity, int direction, p_Room h_roomList, int points, int keyCounter, bool noEnemy, int &timeCounter);
    void getInput(int &key);

    // Menu and Buttons
    void menuChoice(GameEnvironment gameEnvironment, int *key, int *selection);
    void choiceHandler(GameEnvironment gameEnvironment);

    // Bullet handling
    p_bullet generateBullet(Entity entity, p_bullet &bulletList, int dir, bool enemyBull);
    void handleEnemyBullets(Entity player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList);
    void moveBullets(p_bullet h_bulletList);
    void destroyBullet(p_bullet &h_bulletList, int bulletX, int bulletY);
    void bulletCollision(p_bullet &h_bulletList, p_EnemyList h_enemyList, Entity &entity, int &points, int &hearts, bool &pause); // TODO add points here
    void destroySingleBullet(p_bullet &h_bulletList);

    // Enemy handling
    p_EnemyList destroyEnemy(p_EnemyList h_enemyList, Enemy enemy);
    p_EnemyList generateEnemy(GameEnvironment gameEnvironment, int enemyCounter, int roomTracker, p_EnemyList h_enemyList);
    bool checkIfAllEnemiesAreDead(GameEnvironment gameEnvironment, p_EnemyList h_enemyList);

    // Player Stats
    std::tuple<Entity, int> calculateLives(Entity entity, int lives);
    void increasePoints(int &points, int p_add);
    void increaseTimers(int &timer, int &enemyTimer);
    void checkPlayerDeath(Entity &entity, bool &pause, int &hearts);
    void checkMeleeDamage(p_EnemyList h_enemyList, Entity &entity, bool &pause, int &hearts);

    // Items handling
    p_itemList deleteItem(p_itemList itemToDelete, p_itemList h_itemList);
    std::tuple<p_itemList, Entity, int> determineItemEffect(GameEnvironment gameEnvironment, int x, int y, p_itemList h_itemList, Entity entity, int pnt, int keyCounter, RangedWeapon playerWeapon);

    // Ncurses Check
    bool isEmpty(int x, int y);
    bool isItem(int x, int y);
    bool isBullet(int x, int y);
    bool isEnemy(int x, int y);

    // Various
    void mapGenerator();
    void setPause(int direction);

    // Main game engine
    void gameHandler(GameEnvironment gameEnvironment, int direction);
};