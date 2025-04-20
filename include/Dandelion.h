#ifndef DANDELION_H
#define DANDELION_H

#include "Plant.h"

class Dandelion : public Plant {
    void action() override;
public:
    Dandelion(World* world, Point& position);
    Dandelion(World* world, Point& position, int age);
    ~Dandelion();
    bool canReproduceThisTurn() const override;
};

#endif