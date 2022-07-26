#include "weapon.hpp"

class RangedWeapon: public Weapon{

    protected:
        char bulletSkin;     // For the player, bullets stats depends on the weapon
        int bulletSpeed;     // for enemies, it depends by the entity itself
        int bulletRange;

    public: 
        RangedWeapon();
        RangedWeapon(char wpnName[], int dmg, char bSkin, int bSpeed, int bRange);

        void setBulletSkin(char bSkin);
        char getBulletSkin();

        void setBulletSpeed(int bSpeed);
        int getBulletSpeed();

        void setBulletRange(int bRange);
        int getBulletRange();

};