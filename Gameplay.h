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
    char playerInput;
    int shout;
    int width, height;

public:
    Gameplay();
    ~Gameplay();
    void startGame();
    void InitialText();
    void gameInfo();
    void spawnOrganisms();

    void getPlayerInput();
    void handlePlayerInput();
    void makeShout();
    void stats();
    void setGame();
    void endGame();
};



#endif //GAMESTART_H
