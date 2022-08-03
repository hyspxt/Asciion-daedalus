#include "entity.hpp"

Entity::Entity(){}
Entity::Entity(int x, int y, char skin, int lifepoints){
    this->x = x;
    this->y = y;
    this->direction = 0; // The entity is initially not moving
    this->skin = skin;
    this->lifepoints = lifepoints;
}

void Entity::setX(int x){
    this->x = x;
}
int Entity::getX(){
    return(this->x);
}
void Entity::setY(int y){
    this->y = y;
}
int Entity::getY(){
    return(this->y);
}

void Entity::setSkin(char skin){
    this->skin = skin;
}
char Entity::getSkin(){
    return(this->skin);
}

void Entity::setLifePoints(int lifepoints){
    this->lifepoints = lifepoints;
}
int Entity::getLifePoints(){
    return(this->lifepoints);
}
void Entity::increaseLifePoints(int lifepoints){
    this->lifepoints += lifepoints;
}
void Entity::decreaseLifePoints(int lifepoints){
    this->lifepoints -= lifepoints;
}

// Keep in mind that is considered on ncurses
void Entity::dirUp(){
    y--;
}
void Entity::dirDown(){
    y++;
}
void Entity::dirLeft(){
    x--;
}
void Entity::dirRight(){
    x++;
}

void Entity::setRWeapon(RangedWeapon rWeapon){
    this->rWeapon = rWeapon;
}
RangedWeapon Entity::getRWeapon(){
    return(this->rWeapon);
}
void Entity::setRWeaponDamage(int damage){
    this->rWeapon.setDamage(damage);
    
}