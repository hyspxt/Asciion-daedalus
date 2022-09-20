#include <string.h>

class Item
{

protected:
    char itemName[30];
    int id;        // Id determines the effect on the player based on item
    int x;
    int y;
    char skin;      // 'A' -> Artifact, 'K' powers, '?' can be both
    bool isArtifact;     

public:
    Item();
    Item(char itName[], int id, int x, int y, char skin, bool isArtifact);

    void setItemName(char itName[]);
    char* getItemName();

    void setId(int id);
    int getId();

    void setX(int x);
    int getX();

    void setY(int y);
    int getY();

    void setSkin(char skin);
    char getSkin();

    void setIsArtifact(bool isArtifact);
    bool getIsArtifact();
};
struct itemList {
    Item item;
    itemList *next;
};
typedef itemList *p_itemList;