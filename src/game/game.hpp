#include "../gameEnvironment/gameEnvironment.hpp"

#ifndef ENEMY
#define ENEMY
#include "../entity/enemy.hpp"
#endif

#include "../entity/player.hpp"
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

public:
    Game();
    Game(int leftDistance, int rightDistance, int topDistance, int bottomDistance, int maxX, int maxY);

    void ncursesSetup();
    void ncursesStop();

    void movePlayer(Player player);

    void menuChoice(GameEnvironment gameEnvironment, int *key, int *selection);
    void choiceHandler(GameEnvironment gameEnvironment);

    p_bullet generateBullet(Entity entity, p_bullet &bulletList, int dir, bool enemyBull);
    void enemyBullets(Player player, p_EnemyList h_enemyList, p_bullet &h_enemyBulletList);
    void moveBullets(p_bullet h_bulletList);
    void destroyBullet(p_bullet &h_bulletList, int bulletX, int bulletY);

    bool isEmpty(int x, int y);
    bool isItem(int x, int y);
    bool isBullet(int x, int y);
    bool isEnemy(int x, int y);
};