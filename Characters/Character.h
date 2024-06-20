#ifndef PROGRAMMING_III_M1_CHARACTER_H
#define PROGRAMMING_III_M1_CHARACTER_H

#include "../Object.h"
#include "../Point.h"
#include <iostream>
using namespace std;
class Character : public Object{


private:

    int positionX;
    int positionY;
    int healthPoints;


public:
    Character();

    Character(char t, int x, int y, int hp);

    int getPositionX();

    int getPositionY();

    int getHealthPoints();

    void setPosition(int x, int y);

    void setHealthPoints(int hp);
};
#endif //PROGRAMMING_III_M1_CHARACTER_H
