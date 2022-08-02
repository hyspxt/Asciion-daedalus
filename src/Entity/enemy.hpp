#include "entity.hpp"
class Enemy : public Entity
{

protected:
    int killScore; // n. of points given to player when the enemy is killed
    int height;
    int width;
    int meleeDamage; // When the player touch the enemy, it deal this amount of damage

public:
    Enemy();
    Enemy(int x, int y, char skin, int lifepoints, int killScore, int height, int width, int meleeDamage);

    void setKillScore(int killScore);
    int getKillScore();

    void setHeight(int height);
    int getHeight();

    void setWidth(int width);
    int getWidth();

    void setMeleeDamage(int mDamage);
    int getMeleeDamage();
};

struct EnemyList
{
    Enemy enemy;
    EnemyList *next;
};
typedef EnemyList *p_EnemyList;