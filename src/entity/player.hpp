#include "entity.hpp"

class Player : public Entity
{

protected:
    Weapon weapon;

public:
    Player();
    Player(int x, int y, int skin, int lifepoints, Weapon weapon);
};