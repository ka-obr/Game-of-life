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

public:
    Gameplay();
    ~Gameplay();
    void startGame();
};



#endif //GAMESTART_H
