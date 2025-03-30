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
    Point playerPosition;
public:
    World();
    ~World();
    void drawWorld(int height, int width);
    void setDimensions(int height, int width);
    static void drawHorizontalBorder(int width);

    void spawnOrganism(Organism* organism);
    void spawnOrganism(Organism* organism, const Point& position);

    void move(const Point& position, const Point &destination);
    void remove(const Point& position);

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    bool isEmpty(const Point& position);
    Point getRandomNeighbor(const Point& position) const;

    void printOrganismInfo(const Point& position);
    void printShoutSummary();
    void printStatistics();

    Point getPlayerPosition() const;
    void setPlayerPosition(int x, int y);
    void setPlayerPosition(Point& position);

};



#endif //WORLD_H
