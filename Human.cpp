//
// Created by karol on 30.03.2025.
//

#include "include/Human.h"

Human::Human(const Point& position, World* world)
    : Animal(world, 5, 4, position, "🧍") {
    specialAbilityActive = false;
    specialAbilityCooldown = 0;
    specialAbilityCounter = 6;
    
    world->setHuman(this);
}

Human::Human(World* world, int strength, int initiative, Point& position, string symbol, int age)
    : Animal(world, strength, initiative, position, symbol, age) {
    specialAbilityActive = false;
    specialAbilityCooldown = 0;
    specialAbilityCounter = 6;

    world->setHuman(this);
}

Human::Human(World* world, int strength, int initiative, Point& position, string symbol, int age, int specialAbilityActive, int specialAbilityCooldown, int specialAbilityCounter)
    : Animal(world, strength, initiative, position, symbol, age), specialAbilityActive(specialAbilityActive), specialAbilityCooldown(specialAbilityCooldown), specialAbilityCounter(specialAbilityCounter) {

    world->setHuman(this);
}

Human::~Human() {
    // Destructor implementation
}

void Human::tryCollisionAndMove(Point destination) {
    Organism* other = world->getAtCoordinates(destination);
    
    if(haveSavedAttack(*other)) {
        return;
    }
    other = world->getAtCoordinates(destination);
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

    if(specialAbilityCooldown > 0) {
        specialAbilityCooldown--;
    }

    if(specialAbilityActive && specialAbilityCooldown == 0 && this != nullptr) {
        world->killNeighbors(position, 0);
        specialAbilityCounter--;

        if(specialAbilityCounter == 0) {
            specialAbilityActive = false;
            specialAbilityCounter = 5;
            specialAbilityCooldown = 5;
            std::string message = "Human special ability deactivated!!!";
            world->addShoutSummaryMessage(message);
        }
    }
    age++;
}

bool Human::getSpecialAbilityActive() const {
    return specialAbilityActive;
}
void Human::setSpecialAbilityActive(bool specialAbilityActive) {
    this->specialAbilityActive = specialAbilityActive;
}

int Human::getSpecialAbilityCooldown() const {
    return specialAbilityCooldown;
}
int Human::getSpecialAbilityCounter() const {
    return specialAbilityCounter;
}