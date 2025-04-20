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
        std::string message = "Nightshade was eaten by " + other.getSymbol();
        world->addShoutSummaryMessage(message);
        return 0;
    }
    return 0;
}

void Nightshade::reproduce(Point& position) {
    Nightshade* newOrganism = new Nightshade(world, position);
    world->spawnOrganism(newOrganism, position);
    
    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}