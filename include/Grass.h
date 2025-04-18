#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"

class Grass : public Plant {
public:
    Grass(World* world, Point& position);
    Grass(World* world, Point& position, int age);
    ~Grass();

protected:
    void reproduce(Point& position) override;
};


#endif