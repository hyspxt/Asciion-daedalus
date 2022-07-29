#include <string.h>

class Item
{

protected:
    char itemName[30];
    int id;
    int x;
    int y;

public:
    Item();
    Item(char itName[], int id);

    void setId(int id);
    int getId();

    void setX(int x);
    int getX();

    void setY(int y);
    int getY();
};