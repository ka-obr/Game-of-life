//
// Created by karol on 28.03.2025.
//

#include "Organism.h"

Organism::Organism(World &world) : world(world), strength(0), initiative(0), position(Point(0,0)), age(0), alive(true) {
    // Constructor implementation
}

Organism::Organism(World &world, int strength, int initiative, Point position, char symbol) : world(world), strength(strength), initiative(initiative), position(position), age(0), alive(true), symbol(symbol) {
    // Constructor implementation
}

Organism::Organism(World &world, int strength, int initiative, Point position, char symbol, int age) : world(world), strength(strength), initiative(initiative), position(position), age(age), alive(true), symbol(symbol) {
    // Constructor implementation
}

Organism::~Organism() {
    // Destructor implementation
}

int Organism::getStrength() const {
    return strength;
}

int Organism::getInitiative() const {
    return initiative;
}

int Organism::getAge() const {
    return age;
}

int Organism::getSymbol() const {
    return symbol;
}

void Organism::die() {
    //TODO
}

Point& Organism::getPosition() {
    return position;
}

