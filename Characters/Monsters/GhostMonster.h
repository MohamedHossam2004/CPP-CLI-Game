//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_GHOSTMONSTER_H
#define PROGRAMMING_III_M1_GHOSTMONSTER_H

#include "Monster.h"

class GhostMonster : public Monster
{
private:
    bool isVisible;

public:
    GhostMonster(char t, int x, int y, int hp);

    bool isVisibleOnMap() const;

    void setVisible();
};

#endif // PROGRAMMING_III_M1_GHOSTMONSTER_H
