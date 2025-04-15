//
// Created by karol on 28.03.2025.
//

#include "Animal.h"

Animal::Animal(World* world, int strength, int initiative, const Point& position, char symbol)
    : Organism(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Animal::Animal(World* world, int strength, int initiative, const Point& position, char symbol, int age)
    : Organism(world, strength, initiative, position, symbol, age) {
    // Constructor implementation
}

Animal::~Animal() {

}

void Animal::action() {
    Point destination = world->getRandomNeighbor(position);

    if(!world->isWithinBounds(destination)) {
        return;
    }
    if(canMoveTo(destination)) {
        move(destination);
    } 

    //TODO KOLIZJA

    // if {
    //     Organism* other = world->getAtCoordinates(destination);
    //     if (other != nullptr) {
    //         collision(*other);
    //     }
    // }
    age++;
}

bool Animal::collision(Organism& other) {
    if (canEat(other)) {
        eat(other);
        return true;
    }
    return false;
}

void Animal::move(const Point& destination) {
    world->move(position, destination);
    position = destination;
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
