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
    //std::cout << "Guarana reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}

int Guarana::collision(Organism& other) {
    if(this->getStrength() < other.getStrength()) {
        other.setStrength(other.getStrength() + 3);
        return 0;
    }
    return 0;
}


