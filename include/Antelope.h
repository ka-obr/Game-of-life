#ifndef ANTELOPE_H
#define ANTELOPE_H

#include "World.h"
#include "Point.h"
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(World* world, Point& position);
    Antelope(World* world, Point& position, int age);
    ~Antelope();
protected:
    void action() override;
    int collision(Organism& other) override;
    bool haveSavedAttack(Organism& other) override;
    int escapeCollision(Organism& other) override;
};

#endif