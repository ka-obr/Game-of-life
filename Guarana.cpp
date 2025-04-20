#include "include/Guarana.h"

Guarana::Guarana(World* world, Point& position)
    : Plant(world, 0, position, "🍒", 0) {
}

Guarana::Guarana(World* world, Point& position, int age)
    : Plant(world, 0, position, "🍒", age) {
}

Guarana::~Guarana() {

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


