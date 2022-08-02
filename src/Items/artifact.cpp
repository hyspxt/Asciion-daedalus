#include "artifact.hpp"

Artifact::Artifact() : Item::Item(){};
Artifact::Artifact(char itName[], int id, int x, int y, char skin, int lifeBoost) : Item::Item(itName, id, x, y, skin)
{
    this->lifeBoost = lifeBoost;
}

void Artifact::setLifeBoost(int lifeBoost){
    this->lifeBoost = lifeBoost;
}
int Artifact::getLifeBoost(){
    return(this->lifeBoost);
}