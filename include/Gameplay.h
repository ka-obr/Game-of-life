//
// Created by karol on 28.03.2025.
//

#ifndef GAMESTART_H
#define GAMESTART_H

#include "World.h"
#include <set>

enum class OrganismType {
    Wolf,
    Sheep,
    Fox,
    Turtle,
    Grass,
    Dandelion,
    Guarana,
    Nightshade,
    PineBorscht
};

class Gameplay {
private:
    World* world;
    bool running;
    char input;
    int shout;
    int width, height;
    const std::set<int> allowedKeys{'q', 'r', 72, 80, 75, 77, 't', 13};

    void getInput();
    void handleInput();

    void InitialText();
    void gameInfo();
    void spawn(int number, OrganismType type);
    void spawnOrganisms();
    void setGame();
    void endGame();
public:
    Gameplay();
    ~Gameplay();

    void startGame();
    void stats();
    void makeShout();
};

#endif //GAMESTART_H
