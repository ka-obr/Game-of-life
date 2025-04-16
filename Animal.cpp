//
// Created by karol on 28.03.2025.
//

#include "include/Animal.h"

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
        return;
    }

    if(world->getAtCoordinates(destination) != nullptr) {
        Organism* other = world->getAtCoordinates(destination);
        
        collision(*other);
    }
}

bool Animal::collision(Organism& other) {
    if(canKill(other)) {
        kill(other);
        return true;
    }
    if (typeid(other) == typeid(*this)) {
        if(canReproduce(other, position)) {
            reproduce(position);
        }
        return false;
    }
    other.collision(*this);
    return false;
}

void Animal::move(const Point& destination) {
    world->move(position, destination);
    position = destination;
}

void Animal::eat(Organism& other) {
    world->remove(other.getPosition());
}

bool Animal::canKill(const Organism& other) const {
    if(typeid(*this) == typeid(other)) {
        return false;
    }

    return other.canBeKilledBy(*this);
}

bool Animal::canBeKilledBy(const Organism& other) const {
    if(typeid(*this) == typeid(other)) {
        return false;
    }

    return strength < other.getStrength();
}

void Animal::kill(Organism& other) const {
    world->remove(other.getPosition());
}

void Animal::die() {
    world->remove(position);

    //add message to event log
    //std::cout << "Organism died at position: (" << position.x << ", " << position.y << ")" << std::endl;
}

bool Animal::canReproduce(const Organism& other, const Point& position) const {
    if(typeid(*this) == typeid(other) && world->hasFreeSpaceAround(position)) {
        return true;
    }
    return false;
}

void Animal::reproduce(Point& position) {
    // message about reproduction
    //std::cout << "Animal reproduced at position: (" << position.x << ", " << position.y << ")" << std::endl;
}

bool Animal::canMoveTo(const Point& position) const {
    return world->getAtCoordinates(position) == nullptr;
}

bool Animal::canEat(const Organism& other) const {
    return false;
}
