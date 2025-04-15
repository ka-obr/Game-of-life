//
// Created by karol on 28.03.2025.
//

#include "Animal.h"

Animal::Animal(World* world, int strength, int initiative, const Point& position, char symbol)
    : Organism(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Animal::~Animal() {

}

void Animal::action() {
    Point destination = world->getRandomNeighbor(position);
    if (canMoveTo(destination)) {}
        //move(destination);
}

bool Animal::collision(Organism& other) {
    if (canEat(other)) {
        eat(other);
        return true;
    }
    return false;
}

void Animal::eat(Organism& other) {
    world->remove(other.getPosition());
}

void Animal::reproduce(Point& position) {
    // Implementation of reproduce TODO
}

bool Animal::canMoveTo(const Point& position) const {
    return world->getAtCoordinates(position) == nullptr;
}

bool Animal::canEat(const Organism& other) const {
    return false;
}
