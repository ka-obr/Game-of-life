//
// Created by karol on 29.03.2025.
//

#include "include/Plant.h"


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
       Point position = world->getRandomFreeSpaceAround(this->position);
       reproduce(position);
    }
    age++;
}

int Plant::collision(Organism& other) {
    return 0;
}

void Plant::kill(Organism& other) const {
    other.die();

    std::string message = "Organism " + other.getSymbol() + " was killed by " + symbol;
    world->addShoutSummaryMessage(message);
}

bool Plant::canKill(Organism& other) {
    return false; // Plants cannot kill other organisms (normally)
}

void Plant::shouldReceiveStrength(Organism* plant, Organism* animal) {
    // Plants do not receive strength from other organisms
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
    
}
