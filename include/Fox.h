#ifndef FOX_H
#define FOX_H

#include "Animal.h"
#include "World.h"
#include "Point.h"

class Fox : public Animal {
public:
    Fox(World* world, Point& position);
    Fox(World* world, Point& position, int age);
    ~Fox();
    void reproduce(Point& position) override;
    void action() override;
    Point findSafeSpaceAround(Point& position) const;

};


#endif