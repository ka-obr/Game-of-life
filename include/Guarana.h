#ifndef GUARANA_H
#define GUARANA_H

#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(World* world, Point& position);
    Guarana(World* world, Point& position, int age);
    ~Guarana();
protected:
    int collision(Organism& other) override;
};

#endif