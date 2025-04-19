#ifndef NIGHTSHADE_H
#define NIGHTSHADE_H

#include "Plant.h"

class Nightshade : public Plant {
public:
    Nightshade(World* world, const Point& position);
    Nightshade(World* world, const Point& position, int age);
    ~Nightshade();
protected:
    int collision(Organism& other) override;
    void reproduce(Point& position) override;
};

#endif 