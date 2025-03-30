//
// Created by karol on 30.03.2025.
//

#include "Human.h"

Human::Human(const Point& position, World& world)
    : Animal(world, 5, 4, position, 'H') {
    // Constructor implementation
}

Human::Human(World& world, int strength, int initiative, Point& position, char symbol)
    : Animal(world, strength, initiative, position, symbol) {
    // Constructor implementation
}

Human::~Human() {
    // Destructor implementation
}

void Human::action() {
    Point destionation = world.getRandomNeighbor(position);
    if (canMoveTo(destionation)) {
        move(destionation);
    }
}

bool Human::collision(Organism& other) {
    if (canEat(other)) {
        eat(other);
        return true;
    }
    return false;
}

void Human::draw() {
    //world.draw(position, symbol);
}

void Human::move(const Point& position) {
    Animal::move(position);
}

void Human::eat(Organism& other) {
    Animal::eat(other);
}

void Human::reproduce(Point& position) {
    Animal::reproduce(position);
}

bool Human::canMoveTo(const Point& position) const {
    return Animal::canMoveTo(position);
}

bool Human::canEat(const Organism& other) const {
    return Animal::canEat(other);
}



