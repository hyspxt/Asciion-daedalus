#include "item.hpp"

class Artifact : public Item{

    protected:
        int lifeBoost;

    public:
        Artifact();
        Artifact(char itName[], int id, int x, int y, char skin, int lifeBoost);

        void setLifeBoost(int lifeBoost);
        int getLifeBoost();
};