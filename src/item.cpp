#include "item.hpp"

Item::Item(){}
Item::Item(char itName[], int id){
    strcpy(this->itemName, itName);
    this->id = id;
    this->x = x;
    this->y = y;
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