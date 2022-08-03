#include "item.hpp"

Item::Item(){}
Item::Item(char itName[], int id, int x, int y, char skin){
    strcpy(this->itemName, itName);
    this->id = id;
    this->x = x;
    this->y = y;
    this->skin = skin;
}

void Item::setId(int id){
    this->id = id;
}
int Item::getId(){
    return(this->id);
}

void Item::setX(int x){
    this->x = x;
}
int Item::getX(){
    return(this->x);
}
void Item::setY(int y){
    this->y = y;
}
int Item::getY(){
    return(this->y);
}

void Item::setSkin(char skin){
    this->skin = skin;
}
char Item::getSkin(){
    return(this->skin);
}