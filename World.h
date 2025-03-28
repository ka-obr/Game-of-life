//
// Created by karol on 28.03.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <iostream>

#include "Organism.h"
#define WORLD_SIZE 80

using namespace std;

class World {
private:
    Organism* organisms[WORLD_SIZE][WORLD_SIZE];
public:
    World();
    ~World();
    void makeShout();
    void drawWorld();

};



#endif //WORLD_H
