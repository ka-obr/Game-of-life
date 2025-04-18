#include "include/Dandelion.h"

Dandelion::Dandelion(World* world, Point& position)
    : Plant(world, 0, position, "🌽", 0) {
    // Constructor implementation
}

Dandelion::Dandelion(World* world, Point& position, int age)
    : Plant(world, 0, position, "🌽", age) {
    // Constructor implementation
}

Dandelion::~Dandelion() {
    // Destructor implementation
}

void Dandelion::action() {
    int i = 0;
    while(i < 3) {
        if (canReproduceThisTurn() && hasFreeSpace() && age != 0) {
            Point position = world->getRandomFreeSpaceAround(this->position);
            reproduce(position);
            break;
        }
        i++;
    }
    age++;
}

void Dandelion::reproduce(Point& position) {
    Dandelion* newOrganism = new Dandelion(world, position);
    world->spawnOrganism(newOrganism, position);
    //std::cout << "Dandelion reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}

bool Dandelion::canReproduceThisTurn() const {
    return (rand() % 32 == 0);
}
