#include "include/Dandelion.h"

Dandelion::Dandelion(World* world, Point& position)
    : Plant(world, 0, position, "🌽", 0) {

}

Dandelion::Dandelion(World* world, Point& position, int age)
    : Plant(world, 0, position, "🌽", age) {

}

Dandelion::~Dandelion() {

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
}

bool Dandelion::canReproduceThisTurn() const {
    return (rand() % 32 == 0);
}
