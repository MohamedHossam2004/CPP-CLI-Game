//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_GUN_H
#define PROGRAMMING_III_M1_GUN_H
#include <iostream>
using namespace std;
#include "../Object.h"
class Hero;
class Gun : Object
{
private:
    string name;
    int bullets;
    int damage;
    int range;

public:
    Gun(string name, int bullets, int dmg, int range);

    Gun();

    string getName();

    void setName(string name);

    int getBullets();

    void setBullets(int bullets);

    int getDamage();

    void setDamage(int dmg);

    int getRange();

    void setRange(int range);

    virtual ~Gun();

    friend ostream &operator<<(ostream &os, const Gun &gun);

    void useSpecial(Hero &h1, Object ***map);
};
#endif // PROGRAMMING_III_M1_GUN_H
