#include <string.h>

class Item
{

    protected: 
        char itemName[30];
        int id;
        
    public:
        Item();
        Item(char itName[], int id);

        void setId(int id);
        int getId();
};