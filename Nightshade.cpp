#include "include/Nightshade.h"

Nightshade::Nightshade(World* world, const Point& position)
    : Plant(world, 99, position, "🫐", 0) {
    
}

Nightshade::Nightshade(World* world, const Point& position, int age)
    : Plant(world, 99, position, "🫐", age) {
    
}

Nightshade::~Nightshade() {

}

int Nightshade::collision(Organism& other) {
    if(this->getStrength() > other.getStrength()) {
        world->remove(other.getPosition());
        world->remove(this->getPosition());
        return 0;
    }
    return 0;
}

void Nightshade::reproduce(Point& position) {
    Nightshade* newOrganism = new Nightshade(world, position);
    world->spawnOrganism(newOrganism, position);
    //std::cout << "Nightshade reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}