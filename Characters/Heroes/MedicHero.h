//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_MEDICHERO_H
#define PROGRAMMING_III_M1_MEDICHERO_H

#include "Hero.h"

class MedicHero : public Hero
{
private:
    int healingAmount;
    bool usedSpecial = false;

public:
    MedicHero(char t, int x, int y, int hp, int ha);

    int getHealingAmount();

    void useSpecial();

    bool hasUsedSpecial();
};
#endif // PROGRAMMING_III_M1_MEDICHERO_H
