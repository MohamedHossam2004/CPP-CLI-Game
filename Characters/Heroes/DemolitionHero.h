//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_DEMOLITIONHERO_H
#define PROGRAMMING_III_M1_DEMOLITIONHERO_H

#include "Hero.h"

class DemolitionHero : public Hero
{
private:
    Gun *weapon2;
    Gun *curr;

public:
    DemolitionHero(char t, int x, int y, int hp);
    void swapWeapon();
    void useSpecial();
    Gun *getCurrent();
    void setCurrent(Gun *current);
    Gun *getWeapon2();
    void setWeapon2(Gun *weapon2);
};
#endif // PROGRAMMING_III_M1_DEMOLITIONHERO_H
