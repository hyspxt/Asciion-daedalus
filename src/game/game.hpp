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

    // Pause the game execution
    bool pause;

    int timer;
    int enemyTimer;

    p_bullet playerBullets;
    p_bullet enemyBullets;

public:
    Game();
    Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY);

    void ncursesSetup();
    void ncursesStop();

    std::tuple<Entity, int> gameInputs(GameEnvironment gameEnvironment, Entity entity, int direction, p_Room h_roomList, int points, int keyCounter);

    void menuChoice(GameEnvironment gameEnvironment, int *key, int *selection);
    void choiceHandler(GameEnvironment gameEnvironment);

    p_bullet generateBullet(Entity entity, p_bullet &bulletList, int dir, bool enemyBull);
    void handleEnemyBullets(Player player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList);
    void moveBullets(p_bullet h_bulletList);
    void destroyBullet(p_bullet &h_bulletList, int bulletX, int bulletY);
    void bulletCollision(p_bullet &h_bulletList, p_EnemyList h_enemyList, Entity entity, int &points);  //TODO add points here

    p_EnemyList destroyEnemy(p_EnemyList h_enemyList, Enemy enemy);
    p_EnemyList generateEnemy(GameEnvironment gameEnvironment, int enemyCounter, int enemyType, p_EnemyList h_enemyList);

    std::tuple<Entity, int> calculateLives(Entity entity, int lives);

    void getInput(int &key);
    void increasePoints(int &points, int p_add);
    void pointsOverTime(double &points);
    void checkPlayerDeath(Entity entity, bool pause);

    p_itemList deleteItem(p_itemList itemToDelete, p_itemList h_itemList);

    std::tuple<p_itemList, Entity, int> determineItemEffect(GameEnvironment gameEnvironment, int x, int y, p_itemList h_itemList, Entity entity, int pnt, int keyCounter, RangedWeapon playerWeapon); 

    bool isEmpty(int x, int y);
    bool isItem(int x, int y);
    bool isBullet(int x, int y);
    bool isEnemy(int x, int y);

    void mapGenerator();

    void setPause(int direction);

    void gameHandler(GameEnvironment gameEnvironment, int direction);
};