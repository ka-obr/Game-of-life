#include "include/Antelope.h"
#include "include/Turtle.h"
#include "include/Plant.h"

Antelope::Antelope(World* world, Point& position)
: Animal(world, 4, 4, position, "🐐") {
}

Antelope::Antelope(World* world, Point& position, int age)
: Animal(world, 4, 4, position, "🐐", age) {
}

Antelope::~Antelope() {

}

void Antelope::action() {
    if (hasActed) return;
    Point destination = world->getRandomSpaceDoubleMove(position);
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);

        if(haveSavedAttack(*other)) {
            return;
        }
        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1) 
            move(destination);
    }

    age++;
    setHasActed(true);
}

bool Antelope::haveSavedAttack(Organism& other) {
    if (dynamic_cast<const Turtle*>(&other) != nullptr && this->getStrength() < 5) {
        return true;
    }
    return false;
}

int Antelope::escapeCollision(Organism& other) {
    int randomNumber = rand() % 2 + 1;
    if((randomNumber != 0) && (typeid(other) != typeid(*this)) && (dynamic_cast<Plant*>(&other) == nullptr)) {
        Point destination = world->getRandomFreeSpaceAround(position);
        if(world->isWithinBounds(destination)) {
            move(destination);
            setHasActed(true);
            return 1;
        }
    }
    return 0;
}

int Antelope::collision(Organism& other) {
    if(escapeCollision(other) == 1) {
        return 1;
    }
    if(canKill(other)) {
        kill(other);
        return 0;
    }
    if (typeid(other) == typeid(*this)) {
        if(canReproduce(other, position)) {
            reproduce(position);
            setHasActed(true);
        }
        return 1;
    }
    other.collision(*this);
    setHasActed(true);
    return 0;
}

