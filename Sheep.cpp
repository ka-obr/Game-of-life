#include "include/Sheep.h"

Sheep::Sheep(World* world, Point& position)
    : Animal(world, 4, 4, position, "🐑") {
    // Constructor implementation
}

Sheep::Sheep(World* world, Point& position, int age)
    : Animal(world, 4, 4, position, "🐑", age) {
    // Constructor implementation
}

Sheep::~Sheep() {
    // Destructor implementation
}

void Sheep::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Sheep* newOrganism = new Sheep(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    //dodac message o rozmnozeniu do jakiegos info gry
    //std::cout << "Sheep reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}