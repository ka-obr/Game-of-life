//
// Created by karol on 28.03.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <iostream>

#include "Organism.h"
#include "Point.h"
#define WORLD_SIZE 80

using namespace std;

class World {
private:
    int height;
    int width;
    Organism* organisms[WORLD_SIZE][WORLD_SIZE];
public:
    World();
    ~World();
    void makeShout();
    void drawWorld(int height, int width);

    void move(Point position, Point destination);
    void remove(Point position);

    bool isEmpty(Point position);
    Point getRandomNeighbor(const Point& position) const;

};



#endif //WORLD_H
