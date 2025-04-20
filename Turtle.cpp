#include "include/Turtle.h"

Turtle::Turtle(World* world, Point& position)
    : Animal(world, 2, 1, position, "🐢") {
    // Constructor implementation
}

Turtle::Turtle(World* world, Point& position, int age)
    : Animal(world, 2, 1, position, "🐢", age) {
    // Constructor implementation
}

Turtle::~Turtle() {
    // Destructor implementation
}

void Turtle::action(){
    Point destination = world->getRandomNeighbor(position);
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);

        int randomValue = rand() % 4 + 1;
        int status = -1;
        if(other != nullptr) {
            status = collision(*other, randomValue);
        }
        if (status != 1 && randomValue == 1) move(destination);
    }

    age++;
}

int Turtle::collision(Organism& other, int randomValue) {
    if(canKill(other) && randomValue == 1) {
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

void Turtle::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Turtle* newOrganism = new Turtle(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    std::string message = "Organism " + symbol + " reproduced";
    world->addShoutSummaryMessage(message);
}