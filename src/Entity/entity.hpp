#include "../Weapon/weapon.hpp"
#include "../Weapon/rangedWeapon.hpp"

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
        bool enemy;   // true if the entity is an enemy, false otherwise
        RangedWeapon rWeapon;
        p_bullet bullet;

    public:
        Entity();
        Entity(int x, int y, char skin, int lifepoints); // The rest of the parameters aren't needed

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

        void dirUp();
        void dirDown();
        void dirLeft();
        void dirRight();

        void setRWeapon(RangedWeapon rWeapon);
        RangedWeapon getRWeapon();
        void setRWeaponDamage(int damage);
};