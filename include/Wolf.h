#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"
#include "World.h"
#include "Point.h"

class Wolf : public Animal {
public:
    Wolf(World* world, Point& position);
    Wolf(World* world, Point& position, int age);
    ~Wolf();    
};

#endif