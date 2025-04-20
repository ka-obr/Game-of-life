#include "include/Wolf.h"

Wolf::Wolf(World* world, Point& position)
    : Animal(world, 9, 5, position, "🐺") {
    // Constructor implementation
}

Wolf::Wolf(World* world, Point& position, int age)
    : Animal(world, 9, 5, position, "🐺", age) {
    // Constructor implementation
}

Wolf::~Wolf() {
    // Destructor implementation
}

void Wolf::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Wolf* newOrganism = new Wolf(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}


