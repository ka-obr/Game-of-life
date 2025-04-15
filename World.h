//
// Created by karol on 28.03.2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <algorithm>

#include "Organism.h"
#include "Point.h"

using namespace std;

class World {
private:
    int height;
    int width;
    std::vector<Organism*> organisms;
    Organism* human;
public:
    World(int width, int height);
    ~World();
    void drawWorld(int height, int width);
    static void drawHorizontalBorder(int width);

    void update(char input);

    Organism* getAtCoordinates(Point cords) const;

    void spawnOrganism(Organism* organism);
    void spawnOrganism(Organism* organism, const Point& position);

    void move(const Point& position, const Point &destination);
    void remove(const Point& position);

    Point getRandomNeighbor(const Point& position) const;
    bool isWithinBounds(const Point& position) const;
    Point getRandomFreeSpace() const;
    Point getRandomFreeSpaceAround(const Point& position) const;


    void printHumanInfo();
    void printShoutSummary();
    void printStatistics();

    Point getPlayerPosition() const;

    int getWidth();
    int getHeight();

    void setHuman(Organism* org);
};

#endif
