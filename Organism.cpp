//
// Created by karol on 28.03.2025.
//

#include "include/Organism.h"
#include "include/World.h"

Organism::Organism(World* world) : world(world), strength(0), initiative(0), position(Point(0,0)), age(0) {

}

Organism::Organism(World* world, int strength, int initiative, Point position, string symbol) : world(world), strength(strength), initiative(initiative), position(position), age(0), symbol(symbol) {

}

Organism::Organism(World* world, int strength, int initiative, Point position, string symbol, int age) : world(world), strength(strength), initiative(initiative), position(position), age(age), symbol(symbol) {

}

Organism::~Organism() {

}

void Organism::kill(Organism& other) const {
    std::string message = "Organism " + other.getSymbol() + " was killed by " + symbol;
    world->addShoutSummaryMessage(message);
    world->remove(other.getPosition());
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

string Organism::getSymbol() const {
    return symbol;
}

void Organism::die() {

}

int Organism::escapeCollision(Organism& other) {
    return 0; // Default implementation, can be overridden in derived classes
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

void Organism::setAge(int age) {
    this->age = age;
}

void Organism::setStrength(int strength) {
    this->strength = strength;
}

void Organism::setHasActed(bool acted) {
    hasActed = acted;
}

bool Organism::getHasActed() const {
    return hasActed;
}
