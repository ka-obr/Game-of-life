//
// Created by karol on 28.03.2025.
//

#include "include/Organism.h"
#include "include/World.h"

Organism::Organism(World* world) : world(world), strength(0), initiative(0), position(Point(0,0)), age(0) {
    // Constructor implementation
}

Organism::Organism(World* world, int strength, int initiative, Point position, char symbol) : world(world), strength(strength), initiative(initiative), position(position), age(0), symbol(symbol) {
    // Constructor implementation
}

Organism::Organism(World* world, int strength, int initiative, Point position, char symbol, int age) : world(world), strength(strength), initiative(initiative), position(position), age(age), symbol(symbol) {
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

char Organism::getSymbol() const {
    return symbol;
}

void Organism::die() {
    //TODO
}

void Organism::action(char input) {
    action();
}

Point& Organism::getPosition() {
    return position;
}

void Organism::setPosition(Point pos) {
    position = pos;
}
