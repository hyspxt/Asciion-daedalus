
#include "../weapon/rangedWeapon.hpp"

struct bullet{
    int x;
    int y;
    char skin;   // Bullet Skin, based on Ranged Weapon
    double speed;     
    int direction;  // The direction the bullet is flying (chtype)
    bool enemyBullet; // True: enemy shot, False: player shot
    bullet *next;
};
typedef bullet *p_bullet;

class Entity{

    protected:
        int x;
        int y;
        int direction;  //  taken with ncurses Getch() char
        char skin;     // what char appears on screen 
        int lifepoints; 
        int currentLp;
        bool enemy;   // true if the entity is an enemy, false otherwise
        RangedWeapon rWeapon;
        p_bullet bullet;

    public:
        Entity();
        Entity(int x, int y, char skin, int lifepoints); 

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

        void setCurrentLifePoints(int lifepoints);
        int getCurrentLifePoints();
        void increaseCurrentLifePoints(int lifepoints);
        void decreaseCurrentLifePoints(int lifepoints);

        void dirUp();
        void dirDown();
        void dirLeft();
        void dirRight();

        void setRWeapon(RangedWeapon rWeapon);
        RangedWeapon getRWeapon();
        void setRWeaponDamage(int damage);
};