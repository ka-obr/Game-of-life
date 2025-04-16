#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"
#include "World.h"
#include "Point.h"

class Sheep : public Animal {
public:
    Sheep(World* world, Point& position);
    Sheep(World* world, Point& position, int age);
    ~Sheep();
    void reproduce(Point& position) override;

};

#endif 