#include "include/Fox.h"

Fox::Fox(World* world, Point& position)
    : Animal(world, 3, 7, position, "🦊") {
}

Fox::Fox(World* world, Point& position, int age)
    : Animal(world, 3, 7, position, "🦊", age) {
}

Fox::~Fox() {
    
}

void Fox::action() {
    Point destination = world->findSafeSpaceAround(position);
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);
    
        if(haveSavedAttack(*other)) {
            return;
        }
        other = world->getAtCoordinates(destination);
        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1) move(destination);
    }

    age++;
}