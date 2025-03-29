//
// Created by karol on 28.03.2025.
//

#include "Animal.h"

Animal::Animal(World& world, int strength, int initiative, Point& position, char symbol)
    : Organism(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Animal::~Animal() {

}

void Animal::action() {
    Point destination = world.getRandomNeighbor(position);
    if (canMoveTo(destination))
        move(destination);
}

bool Animal::collision(Organism& other) {
    if (canEat(other)) {
        eat(other);
        return true;
    }
    return false;
}

// void Animal::draw() {
//     // Implementation of draw TODO
// }

void Animal::move(const Point& destination) {
    world.move(position, destination);
    position = destination;
}

void Animal::eat(Organism& other) {
    world.remove(other.getPosition());
}

void Animal::reproduce(Point& position) {
    // Implementation of reproduce TODO
}

bool Animal::canMoveTo(const Point& position) const {
    return world.isEmpty(position);
}

bool Animal::canEat(const Organism& other) const {
    return false;
}
