#include "weapon.hpp"

class RangedWeapon: public Weapon{

    protected:
        char bulletSkin;
        int bulletSpeed;
        int bulletRange;

    public: 
        RangedWeapon();
        RangedWeapon(char bSkin, int bSpeed, int bRange);

        void setBulletSkin(char bSkin);
        char getBulletSkin();

        void setBulletSpeed(int bSpeed);
        int getBulletSpeed();

        void setBulletRange(int bRange);
        int getBulletRange();

};