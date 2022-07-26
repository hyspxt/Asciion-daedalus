#include <string.h>

class Weapon {

    protected:
        char weaponName[20];
        int damage;       // Damage per hit

    public:
        Weapon();
        Weapon(char wpnName[], int dmg);

        void setDamage(int dmg);
        int getDamage();
        void increaseDamage(int plusDmg);
        void decreaseDamage(int lessDmg);
};

struct WeaponList {
    Weapon weapon;
    WeaponList *next;
};
typedef WeaponList *p_WeaponList;