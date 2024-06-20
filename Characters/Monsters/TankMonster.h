//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_TANKMONSTER_H
#define PROGRAMMING_III_M1_TANKMONSTER_H

#include "Monster.h"

class TankMonster : public Monster {
private:
    int shield;
public:
    TankMonster(char t, int x, int y, int hp, int s);

    int getShield() const;

    void setShield(int shield);
};
#endif //PROGRAMMING_III_M1_TANKMONSTER_H
