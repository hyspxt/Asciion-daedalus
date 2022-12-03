#include "enemy.hpp"

Enemy::Enemy() : Entity::Entity() {} // First the son, then the father
Enemy::Enemy(int x, int y, char skin, int lifepoints, int killScore, int meleeDamage)
    : Entity::Entity(x, y, skin, lifepoints)
{
    this->killScore = killScore;
}

void Enemy::setKillScore(int killScore)
{
    this->killScore = killScore;
}
int Enemy::getKillScore()
{
    return (this->killScore);
}

void Enemy::setMeleeDamage(int mDamage)
{
    this->meleeDamage = mDamage;
}
int Enemy::getMeleeDamage()
{
    return (this->meleeDamage);
}