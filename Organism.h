//
// Created by karol on 28.03.2025.
//

#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
#include "Point.h"


class World;

using namespace std;


class Organism {
private:
    int strength;
    int initiative;
    Point position;
    int age;
    bool alive;
    char symbol;
    World& world;
public:
    Organism(World& world);
    Organism(World& world, int strength, int initiative, Point position, char symbol);
    Organism(World& world, int strength, int initiative, Point position, char symbol, int age);
    virtual ~Organism();

    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual void draw() = 0;

    int getStrength() const;
    int getInitiative() const;
    int getPosition() const;
    int getAge() const;
    int getSymbol() const;
    Point& getPoint();
};



#endif //ORGANISM_H
