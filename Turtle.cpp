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
    int rand = std::rand() % 4 + 1; // Random number between 1 and 4
    if(world->isWithinBounds(destination) && age != 0) {
        Organism* other = world->getAtCoordinates(destination);

        int status = -1;
        if(other != nullptr) {
            status = collision(*other);
        }
        if (status != 1 && rand == 1) move(destination);
    }

    age++;
}

void Turtle::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Turtle* newOrganism = new Turtle(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    //dodac message o rozmnozeniu do jakiegos info gry
    //std::cout << "Turtle reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}