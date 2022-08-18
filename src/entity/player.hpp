
#ifndef ENTITY
#define ENTITY
#include "entity.hpp"
#endif

class Player : public Entity
{

protected:
    Weapon weapon;

public:
    Player();
    Player(int x, int y, int skin, int tmpLifepoints, Weapon weapon);
};