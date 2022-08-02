#include "weapon.hpp"
#include <string.h>
#include <iostream>

Weapon::Weapon() {}
Weapon::Weapon(char wpnName[], int dmg)
{
    strcpy(this->weaponName, wpnName);
    this->damage = dmg;
}

void Weapon::setDamage(int dmg)
{
    this->damage = dmg;
}
int Weapon::getDamage()
{
    return (this->damage);
}
void Weapon::increaseDamage(int dmg)
{
    this->damage += dmg;
}
void Weapon::decreaseDamage(int dmg)
{
    this->damage -= dmg;
}