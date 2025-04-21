#include "include/PineBorscht.h"

PineBorscht::PineBorscht(World* world, Point& position)
    : Plant(world, 10, position, "💮", 0) {
}

PineBorscht::PineBorscht(World* world, Point& position, int age)
    : Plant(world, 10, position, "💮", age) {
}

PineBorscht::~PineBorscht() {
}

void PineBorscht::action() {
    if(age != 0) {
        world->killNeighbors(position, 1);

        if (canReproduceThisTurn() && hasFreeSpace()) {
            reproduce(this->position);
        }
    }
    age++;
}

int PineBorscht::collision(Organism& other) {
    world->remove(other.getPosition());
    world->remove(this->getPosition());
    std::string message = "Pine Borscht was eaten by " + other.getSymbol();
    world->addShoutSummaryMessage(message);
    return 0;
}
