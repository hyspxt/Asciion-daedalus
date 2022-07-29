#include "power.hpp"

Power::Power() : Item::Item(){};
Power::Power(char itName[], int id, int x, int y, char skin, int healValue) : Item::Item(itName, id, x, y, skin)
{
    this->healValue = healValue;
}

void Power::setHealValue(int healValue){
    this->healValue = healValue;
}
int Power::getHealValue(){
    return(this->healValue);
}