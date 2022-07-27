#include "player.hpp"

Player::Player() : Entity::Entity(){}
Player::Player(int x, int y, int skin, int lifepoints, Weapon weapon, RangedWeapon rWeapon)
    : Entity::Entity(x, y, skin, lifepoints, 0){}
