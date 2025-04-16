//
// Created by karol on 30.03.2025.
//

#include "include/Human.h"

Human::Human(const Point& position, World* world)
    : Animal(world, 5, 4, position, 'H') {
    
    world->setHuman(this);
}

Human::Human(World* world, int strength, int initiative, Point& position, char symbol, int age)
    : Animal(world, strength, initiative, position, symbol, age) {
    
    world->setHuman(this);
}

Human::~Human() {
    // Destructor implementation
}

void Human::tryCollisionAndMove(Point destination) {
    Organism* other = world->getAtCoordinates(destination);
    
    int status = -1;
    if(other != nullptr) {
        status = collision(*other);
    }
    if (status != 1) move(destination);
}

void Human::action(char input) {
    switch (input) {
        case 72: // strzałka w górę
            if (position.y > 0) {
                tryCollisionAndMove(Point(position.x, position.y - 1));
            }
            break;
        case 80: // strzałka w dół
            if (position.y < world->getHeight() - 1) {
                tryCollisionAndMove(Point(position.x, position.y + 1));
            }
            break;
        case 75: // strzałka w lewo
            if (position.x > 0) {
                tryCollisionAndMove(Point(position.x - 1, position.y));
            }
            break;
        case 77: // strzałka w prawo
            if (position.x < world->getWidth() - 1) {
                tryCollisionAndMove(Point(position.x + 1, position.y));
            }
            break;
        default:
            break;
    }
    age++;
}