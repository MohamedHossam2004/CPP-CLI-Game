//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_GAME_H
#define PROGRAMMING_III_M1_GAME_H
#include "../Object.h"
#include "../Characters/Heroes/Hero.h"

class Game
{
private:
    static const int rows = 15;
    static const int cols = 15;
    static int round;
    Object ***grid;
    Hero *hero;

public:
    Game();

    ~Game();

    Hero *getHero();

    void generateMap();

    void showMap();

    void startGame();

    void FireGun(char direction);

    void useGunSpecial();

    void move(Hero &h1, char direction);

    int checkGameOver();

    void updateMap();

    int getRound();

    void increaseRound();
};
#endif // PROGRAMMING_III_M1_GAME_H
