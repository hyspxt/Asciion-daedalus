#include "item.hpp"

Item::Item(){}
Item::Item(char itName[], int id){
    strcpy(this->itemName, itName);
    this->id = id;
}

void Item::setId(int id){
    this->id = id;
}
int Item::getId(){
    return(this->id);
}