#include "enemy.hpp"

Enemy::Enemy() : Entity::Entity() {} // First the son, then the father
Enemy::Enemy(int x, int y, char skin, int lifepoints, int killScore, int height, int width, int meleeDamage)
    : Entity::Entity(x, y, skin, lifepoints)
{
    this->killScore = killScore;
    this->height = height;
    this->width = width;
}

void Enemy::setKillScore(int killScore)
{
    this->killScore = killScore;
}
int Enemy::getKillScore()
{
    return (this->killScore);
}

void Enemy::setHeight(int height)
{
    this->height = height;
}
int Enemy::getHeight()
{
    return (this->height);
}

void Enemy::setWidth(int width)
{
    this->width = width;
}
int Enemy::getWidth()
{
    return (this->width);
}

void Enemy::setMeleeDamage(int mDamage)
{
    this->meleeDamage = mDamage;
}
int Enemy::getMeleeDamage()
{
    return (this->meleeDamage);
}