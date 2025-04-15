#include "Wolf.h"

Wolf::Wolf(World* world, Point& position)
    : Animal(world, 9, 5, position, 'W') {
    // Constructor implementation
}

Wolf::Wolf(World* world, Point& position, int age)
    : Animal(world, 9, 5, position, 'W', age) {
    // Constructor implementation
}

Wolf::~Wolf() {
    // Destructor implementation
}

void Wolf::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Wolf* newOrganism = new Wolf(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    //dodac message o rozmnozeniu do jakiegos info gry
    //std::cout << "Wolf reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}


