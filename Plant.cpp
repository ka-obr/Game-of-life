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

    //message o zabiciu
    //cout << "Zabito " << other.getSymbol() << " na pozycji " << other.getPosition() << endl;
}

bool Plant::canKill(const Organism& other) const {
    return false; // Plants cannot kill other organisms (normally)
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
