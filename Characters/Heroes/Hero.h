//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_HERO_H
#define PROGRAMMING_III_M1_HERO_H

#include "../Character.h"
#include "../../Weapons/Gun.h"

class Hero : public Character
{
public:
    Gun *weapon;

public:
    Hero(char t, int x, int y, int hp);

    Gun *getWeapon();

    void setWeapon(Gun *g);

    ~Hero();

    friend ostream &operator<<(ostream &os, Hero &hero);

    virtual void useSpecial() = 0;
};
#endif // PROGRAMMING_III_M1_HERO_H
