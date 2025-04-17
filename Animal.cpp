//
// Created by karol on 28.03.2025.
//

#include "include/Animal.h"
#include "include/Turtle.h"

Animal::Animal(World* world, int strength, int initiative, const Point& position, string symbol)
    : Organism(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Animal::Animal(World* world, int strength, int initiative, const Point& position, string symbol, int age)
    : Organism(world, strength, initiative, position, symbol, age) {
    // Constructor implementation
}

Animal::~Animal() {

}

void Animal::action() {
    Point destination = world->getRandomNeighbor(position);
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);

        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1) move(destination);
    }

    age++;
}

int Animal::collision(Organism& other) {
    if (haveSavedAttack(other)) {
        return 1;
    }
    if(canKill(other)) {
        kill(other);
        return 0;
    }
    if (typeid(other) == typeid(*this)) {
        if(canReproduce(other, position)) {
            reproduce(position);
        }
        return 1;
    }
    other.collision(*this);
    return 0;
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

    return strength >= other.getStrength();
}

void Animal::kill(Organism& other) const {
    world->remove(other.getPosition());
}

void Animal::die() {
    world->remove(position);

    //add message to event log
    //std::cout << "Organism died at position: (" << position.x << ", " << position.y << ")" << std::endl;
}

bool Animal::haveSavedAttack(const Organism& other) const {
    if (dynamic_cast<const Turtle*>(&other) != nullptr && this->getStrength() < 5 && dynamic_cast<const Turtle*>(this) == nullptr) {
        return true;
    }
    return false;
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

bool Animal::canEat(const Organism& other) const {
    return false;
}
