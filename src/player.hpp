#include "entity.hpp"
#include "weapon.hpp"

class Player : public Entity
{

protected:
    Weapon weapon;
    RangedWeapon rWeapon;

public:
    Player();
    Player(int x, int y, int skin, int lifepoints, Weapon weapon, RangedWeapon rWeapon);
};