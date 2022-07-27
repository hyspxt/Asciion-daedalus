#include "entity.hpp"
class Enemy : public Entity
{

protected:
    int killScore; // n. of points given to player when the enemy is killed
    int height;
    int width;

public:
    Enemy();
    Enemy(int x, int y, char skin, int lifepoints, int damage, int killScore, int height, int width);

    void setKillScore(int killScore);
    int getKillScore();

    void setHeight(int height);
    int getHeight();

    void setWidth(int width);
    int getWidth();
};

struct EnemyList
{
    Enemy enemy;
    EnemyList *next;
};
typedef EnemyList *p_EnemyList;