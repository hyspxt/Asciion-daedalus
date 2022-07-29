#include "item.hpp"

class Power : public Item{

    protected:
        int healValue;
    
    public:
        Power();
        Power(char itName[], int id, int x, int y, char skin, int healValue);

        void setHealValue(int healValue);
        int getHealValue();
};