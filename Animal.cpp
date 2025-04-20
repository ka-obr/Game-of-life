//
// Created by karol on 28.03.2025.
//

#include "include/Animal.h"
#include "include/Turtle.h"
#include "include/Guarana.h"
#include "include/Wolf.h"
#include "include/Fox.h"
#include "include/Sheep.h"

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

        if(haveSavedAttack(*other)) {
            return;
        }
        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1) move(destination);
    }

    age++;
}

int Animal::collision(Organism& other) {
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

void Animal::shouldReceiveStrength(Organism* plant, Organism* animal) {
    if (dynamic_cast<Guarana*>(plant) != nullptr) {
        plant->collision(*animal);
    }
}

bool Animal::canKill(Organism& other) {
    if(typeid(*this) == typeid(other)) {
        return false;
    }
    shouldReceiveStrength(&other, this);

    return strength >= other.getStrength();
}

void Animal::die() {
    world->remove(position);
}

bool Animal::haveSavedAttack(const Organism& other) const {
    if (dynamic_cast<const Turtle*>(&other) != nullptr && this->getStrength() < 5) {
        return true;
    }
    return false;
}

Animal* Animal::createAnimalByType(const Organism* parent, World* world, Point& position) {
    if (typeid(*parent) == typeid(Wolf)) {
        return new Wolf(world, position);
    } else if (typeid(*parent) == typeid(Sheep)) {
        return new Sheep(world, position);
    } else if (typeid(*parent) == typeid(Fox)) {
        return new Fox(world, position);
    } else if (typeid(*parent) == typeid(Turtle)) {
        return new Turtle(world, position);
    }
    return nullptr;
}

bool Animal::canReproduce(const Organism& other, const Point& position) const {
    if(typeid(*this) == typeid(other) && world->hasFreeSpaceAround(position)) {
        return true;
    }
    return false;
}

// void Animal::reproduce(Point& position) {
//     std::string message = "Organism " + symbol + " reproduced";
//     world->addShoutSummaryMessage(message);
// }

void Animal::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Organism* parent = world->getAtCoordinates(position);

    Animal* newAnimal = createAnimalByType(parent, world, freeSpace);
    world->spawnOrganism(newAnimal, freeSpace);

    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}

bool Animal::canEat(const Organism& other) const {
    return false;
}
