//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_AMMO_H
#define PROGRAMMING_III_M1_AMMO_H

#include "Item.h"

class Ammo : public Item {
private:
    int bullets;
public:
    Ammo(int b);

    int getBullets() const;
};


#endif //PROGRAMMING_III_M1_AMMO_H
