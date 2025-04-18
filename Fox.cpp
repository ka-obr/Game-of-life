#include "include/Fox.h"

Fox::Fox(World* world, Point& position)
    : Animal(world, 3, 7, position, "🦊") {
    // Constructor implementation
}

Fox::Fox(World* world, Point& position, int age)
    : Animal(world, 3, 7, position, "🦊", age) {
    // Constructor implementation
}

Fox::~Fox() {
    // Destructor implementation
}

void Fox::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Fox* newOrganism = new Fox(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    //dodac message o rozmnozeniu do jakiegos info gry
    //std::cout << "Fox reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}

void Fox::action() {
    Point destination = world->findSafeSpaceAround(position);
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);
    
        if(haveSavedAttack(*other)) {
            return;
        }
        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1) move(destination);
    }

    age++;
}

