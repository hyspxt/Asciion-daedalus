
#ifndef ENTITY
#define ENTITY
#include "entity.hpp"
#endif

class Enemy : public Entity
{

protected:
    int killScore; // n. of points given to player when the enemy is killed
    int meleeDamage; // When the player touch the enemy with body or bullet, it deal this amount of damage

public:
    Enemy();
    Enemy(int x, int y, char skin, int lifepoints, int killScore, int meleeDamage);

    void setKillScore(int killScore);
    int getKillScore();

    void setMeleeDamage(int mDamage);
    int getMeleeDamage();
};

struct EnemyList
{
    Enemy enemy;
    EnemyList *next;
};
typedef EnemyList *p_EnemyList;