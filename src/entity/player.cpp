#include "player.hpp"

Player::Player() : Entity::Entity(){}
Player::Player(int x, int y, int skin, int tmpLifepoints, Weapon weapon)
    : Entity::Entity(x, y, skin, tmpLifepoints){}
