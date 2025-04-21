//
// Created by karol on 29.03.2025.
//

#include "include/Plant.h"
#include "include/Grass.h"
#include "include/Dandelion.h"
#include "include/Guarana.h"
#include "include/Nightshade.h"
#include "include/PineBorscht.h"
#include "include/World.h"


Plant::Plant(World* world, const Point& position, string symbol)
    : Organism(world, strength, 0, position, symbol) {
    // Constructor implementation
}

Plant::Plant(World* world, int strength, const Point& position, string symbol, int age)
    : Organism(world, strength, 0, position, symbol, age) {
    // Constructor implementation
}

Plant::Plant(World* world, int strength, string symbol)
    : Organism(world, strength, 0, Point(0, 0), symbol) {
    // Constructor implementation
}

Plant::~Plant() {
    // Destructor implementation
}

void Plant::action() {
    if (canReproduceThisTurn() && hasFreeSpace() && age != 0) {
       reproduce(this->position);
    }
    age++;
}

int Plant::collision(Organism& other) {
    return 0;
}

bool Plant::canKill(Organism& other) {
    return false; // Plants cannot kill other organisms (normally)
}

void Plant::shouldReceiveStrength(Organism* plant, Organism* animal) {
    // Plants do not receive strength from other organisms
}

Plant* Plant::createPlantByType(const Organism* parent, World* world, Point& position) {
    if (typeid(*parent) == typeid(Grass)) {
        return new Grass(world, position);
    } else if (typeid(*parent) == typeid(Dandelion)) {
        return new Dandelion(world, position);
    } else if (typeid(*parent) == typeid(Guarana)) {
        return new Guarana(world, position);
    } else if (typeid(*parent) == typeid(Nightshade)) {
        return new Nightshade(world, position);
    } else if (typeid(*parent) == typeid(PineBorscht)) {
        return new PineBorscht(world, position);
    } else {
        return nullptr;
    }
}

void Plant::die() {
    world->remove(position);
}

bool Plant::hasFreeSpace() const {
    return world->hasFreeSpaceAround(position);
}

bool Plant::canReproduceThisTurn() const {
    return (rand() % 20 == 0);
}

void Plant::reproduce(Point& position) {
    Point newPosition = world->getRandomFreeSpaceAround(position);
    Organism* parent = world->getAtCoordinates(position);

    Plant* newPlant = createPlantByType(parent, world, newPosition);
    world->spawnOrganism(newPlant, newPosition);

    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}
