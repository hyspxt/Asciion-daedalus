#include "weapon.hpp"
#include "rangedWeapon.hpp"

struct bullet{
    int x;
    int y;
    char skin;
    double speed;      
    bool enemyBullet; // True: enemy shot, False: player shot
    bullet *next;
};
typedef bullet *p_bullet;

class Entity{

    protected:
        int x;
        int y;
        int direction;  // ncurses Getch() char
        char skin;
        int lifepoints;
        int damage;   // In this case, refers to the melee damage and bullet damage (player stat are calculated in another way)
        bool enemy;   // true if the entity is an enemy, false otherwise
        p_bullet bullet;

    public:
        Entity();
        Entity(int x, int y, char skin, int lifepoints, int damage); // The rest of the parameters aren't needed

        void setX(int x);
        int getX();
        void setY(int y);
        int getY();

        void setSkin(char skin);
        char getSkin();

        void setLifePoints(int lifepoints);
        int getLifePoints();
        void increaseLifePoints(int lifepoints);
        void decreaseLifePoints(int lifepoints);

        void setDamage(int damage);
        int getDamage();
        void increaseDamage(int damage);

        void dirUp();
        void dirDown();
        void dirLeft();
        void dirRight();
};