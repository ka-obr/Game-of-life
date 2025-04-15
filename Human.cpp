//
// Created by karol on 30.03.2025.
//

#include "Human.h"

Human::Human(const Point& position, World* world)
    : Animal(world, 5, 4, position, 'H') {
    
    world->setHuman(this);
}

Human::Human(World* world, int strength, int initiative, Point& position, char symbol)
    : Animal(world, strength, initiative, position, symbol) {
    
    world->setHuman(this);
}

Human::~Human() {
    // Destructor implementation
}

void Human::action(char input) {
    switch (input) {
        case 72: // strzałka w górę
            if (position.y > 0) {
                position.y--;
            }
            break;
        case 80: // strzałka w dół
            if (position.y < world->getHeight() - 1) {
                position.y++;
            }
            break;
        case 75: // strzałka w lewo
            if (position.x > 0) {
                position.x--;
            }
            break;
        case 77: // strzałka w prawo
            if (position.x < world->getWidth() - 1) {
                position.x++;
            }
            break;
        default:
            break;
    }
    age++;
}