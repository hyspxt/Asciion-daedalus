#include "entity.hpp"

Entity::Entity() {}
Entity::Entity(int x, int y, char skin, int lifepoints)
{
    this->x = x;
    this->y = y;
    this->direction = 0; // The entity is initially not moving in any direction
    this->skin = skin;
    this->lifepoints = lifepoints; // This is the max amount that the entity can reach-> used only for the player
    this->currentLp = lifepoints;  // Current amount of LP
}

void Entity::setX(int x)
{
    this->x = x;
}
int Entity::getX()
{
    return (this->x);
}
void Entity::setY(int y)
{
    this->y = y;
}
int Entity::getY()
{
    return (this->y);
}

void Entity::setSkin(char skin)
{
    this->skin = skin;
}
char Entity::getSkin()
{
    return (this->skin);
}

void Entity::setLifePoints(int lifepoints)
{
    this->lifepoints = lifepoints;
}
int Entity::getLifePoints()
{
    return (this->lifepoints);
}
void Entity::increaseLifePoints(int lifepoints)
{
    this->lifepoints += lifepoints;
}
void Entity::decreaseLifePoints(int lifepoints)
{
    this->lifepoints -= lifepoints;
}

void Entity::setCurrentLifePoints(int currentLp)
{
    this->currentLp = currentLp;
}
int Entity::getCurrentLifePoints()
{
    return (this->currentLp);
}
void Entity::increaseCurrentLifePoints(int currentLp)
{
    // Current LP can't go over maxLp
    if (this->currentLp < this->lifepoints)
        this->currentLp += currentLp;
    if (this->currentLp >= this->lifepoints)
        this->currentLp = this->lifepoints;
}
void Entity::decreaseCurrentLifePoints(int currentLp)
{
    this->currentLp -= currentLp;
}

// Keep in mind that is considered on ncurses
void Entity::dirUp()
{
    this->y--;
}
void Entity::dirDown()
{
    this->y++;
}
void Entity::dirLeft()
{
    this->x--;
}
void Entity::dirRight()
{
    this->x++;
}

void Entity::setRWeapon(RangedWeapon rWeapon)
{
    this->rWeapon = rWeapon;
}
RangedWeapon Entity::getRWeapon()
{
    return (this->rWeapon);
}
void Entity::setRWeaponDamage(int damage)
{
    this->rWeapon.setDamage(damage);
}