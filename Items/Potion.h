//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_POTION_H
#define PROGRAMMING_III_M1_POTION_H

#include "Item.h"

class Potion : public Item {
private:
    int healingAmount;
public:
    Potion(int ha);

    int getHealingAmount() const;
};
#endif //PROGRAMMING_III_M1_POTION_H
