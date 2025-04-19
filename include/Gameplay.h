//
// Created by karol on 28.03.2025.
//

#ifndef GAMESTART_H
#define GAMESTART_H

#include "World.h"

class Gameplay {
private:
    World* world;
    bool running;
    char input;
    int shout;
    int width, height;

public:
    Gameplay();
    ~Gameplay();
    void startGame();
    void InitialText();
    void gameInfo();
    void spawnWolves(int number);
    void spawnSheep(int number);
    void spawnFoxes(int number);
    void spawnTurtles(int number);
    void spawnGrass(int number);
    void spawnDandelions(int number);
    void spawnGuarana(int number);
    void spawnOrganisms();

    void getInput();
    void handleInput();
    void makeShout();
    void stats();
    void setGame();
    void endGame();
};

#endif //GAMESTART_H
