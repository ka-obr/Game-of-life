//
// Created by karol on 29.03.2025.
//

#include "include/Plant.h"


Plant::Plant(World* world, const Point& position, char symbol)
    : Organism(world, 0, initiative, position, symbol) {
    // Constructor implementation
}

Plant::Plant(World* world, int strength, const Point& position, char symbol)
    : Organism(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Plant::Plant(World* world, int strength, char symbol)
    : Organism(world, strength, initiative, Point(0, 0), symbol) {
    // Constructor implementation
}

Plant::~Plant() {
    // Destructor implementation
}

void Plant::action() {
    if (hasFreeSpace() && canReproduce()) {
        Point position = world->getRandomNeighbor(this->position);
        if (world->getAtCoordinates(position) == nullptr) {
            reproduce(position);
        }
    }
}

int Plant::collision(Organism& other) {
    if (other.getPosition() == position) {
        reproduce(other.getPosition());
        return 1;
    }
    return 0;
}

void Plant::die() {
    world->remove(position);
}

bool Plant::hasFreeSpace() const {
    //return world.hasFreeSpace(position);
    return true;
}

bool Plant::canReproduce() const {
    return (rand() % 12 == 0);
}

void Plant::reproduce(Point& position) {
    if (world->getAtCoordinates(position) == nullptr) {
        //TODO
    }
}
