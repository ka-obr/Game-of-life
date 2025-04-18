#ifndef TURTLE_H
#define TURTLE_H

#include "Animal.h"
#include "World.h"
#include "Point.h"

class Turtle : public Animal {
public:
    Turtle(World* world, Point& position);
    Turtle(World* world, Point& position, int age);
    ~Turtle();
    void reproduce(Point& position) override;
    int collision(Organism& other, int randomValue);
    void action() override;
};


#endif