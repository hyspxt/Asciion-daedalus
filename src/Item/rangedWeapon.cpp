#include "rangedWeapon.hpp"

RangedWeapon::RangedWeapon(){}
RangedWeapon::RangedWeapon(char wpnName[], int dmg, char bSKin, int bSpeed, int bRange){

    strcpy(weaponName, wpnName);
    this->damage = dmg;
    this->bulletSkin = bSKin;
    this->bulletSpeed = bSpeed;
    this->bulletRange = bRange;

}

void RangedWeapon::setBulletSkin(char bSkin){
    this->bulletSkin = bSkin;
}
char RangedWeapon::getBulletSkin(){
    return(this->bulletSkin);
}

void RangedWeapon::setBulletSpeed(int bSpeed){
    this->bulletSpeed = bSpeed;
}
int RangedWeapon::getBulletSpeed(){
    return(this->bulletSpeed);
}

void RangedWeapon::setBulletRange(int bRange){
    this->bulletRange = bRange;
}
int RangedWeapon::getBulletRange(){
    return(this->bulletRange);
}