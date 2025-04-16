#include "include/Fox.h"

Fox::Fox(World* world, Point& position)
    : Animal(world, 3, 7, position, 'F') {
    // Constructor implementation
}

Fox::Fox(World* world, Point& position, int age)
    : Animal(world, 3, 7, position, 'F', age) {
    // Constructor implementation
}

Fox::~Fox() {
    // Destructor implementation
}

void Fox::reproduce(Point& position) {
    Point freeSpace = world->getRandomFreeSpaceAround(position);

    Fox* newOrganism = new Fox(world, freeSpace);
    world->spawnOrganism(newOrganism, freeSpace);


    //dodac message o rozmnozeniu do jakiegos info gry
    //std::cout << "Fox reproduced at position: (" << freeSpace.x << ", " << freeSpace.y << ")" << std::endl;
}

Point Fox::findSafeSpaceAround(Point& position) const {
    std::vector<vector<int>> displaces = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    // Tworzenie generatora liczb losowych
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Przetasowanie indeksów
    std::shuffle(displaces.begin(), displaces.end(), rng);

    for (vector<int> displace : displaces) {
        Point neighbor(position.x + displace[0], position.y + displace[1]);

        Organism* other = world->getAtCoordinates(neighbor);
        if (other != nullptr && other->getStrength() > strength) {
            continue; // Skip if the neighbor is stronger
        }

        if (world->isWithinBounds(neighbor)) {
            return neighbor;
        }
    }
    return position;
}

void Fox::action() {
    Point destination = findSafeSpaceAround(position);
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

