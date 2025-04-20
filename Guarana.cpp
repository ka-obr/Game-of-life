#include "include/Guarana.h"

Guarana::Guarana(World* world, Point& position)
    : Plant(world, 0, position, "🍒", 0) {
}

Guarana::Guarana(World* world, Point& position, int age)
    : Plant(world, 0, position, "🍒", age) {
}

Guarana::~Guarana() {

}

void Guarana::reproduce(Point& position) {
    Guarana* newOrganism = new Guarana(world, position);
    world->spawnOrganism(newOrganism, position);

    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}

int Guarana::collision(Organism& other) {
    if(this->getStrength() < other.getStrength()) {
        other.setStrength(other.getStrength() + 3);

        std::string message = "Guarana was eaten by " + other.getSymbol();
        world->addShoutSummaryMessage(message);
        return 0;
    }
    return 0;
}


