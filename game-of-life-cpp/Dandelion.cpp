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
            reproduce(this->position);
            break;
        }
        i++;
    }
    age++;
}

bool Dandelion::canReproduceThisTurn() const {
    return (rand() % 32 == 0);
}
