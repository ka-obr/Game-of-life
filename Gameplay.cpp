//
// Created by karol on 28.03.2025.
//

#include "include/Gameplay.h"
#include "include/Human.h"
#include "include/Wolf.h"
#include "include/Sheep.h"
#include "include/Fox.h"
#include "include/Turtle.h"
#include "include/Grass.h"
#include "include/Dandelion.h"
#include "include/Guarana.h"
#include "include/Nightshade.h"
#include <conio.h>

using namespace std;

Gameplay::Gameplay() {
    running = true;
    input = ' ';
    shout = 0;
}

Gameplay::~Gameplay() {
    delete world;
}

void Gameplay::startGame() {

    InitialText();
    getInput();
    gameInfo();
    getInput();
    setGame();
    spawnOrganisms();
    world->drawWorld(width, height);

    while (running) {
        getInput();
        handleInput();
        if (!running) {
            break;
        }

        world->update(input);

        world->drawWorld(width, height);
        world->printHumanInfo();
        world->printShoutSummary();
        makeShout();
    }

    endGame();
}

void Gameplay::InitialText() {
    cout << "Welcome to the game!" << endl;
    cout << "Author: Karol Obrycki" << endl;
    cout << "Index: 203264" << endl;
    cout << "Press any key to get know about the game..." << endl;
}

void Gameplay::setGame() {
    system("cls");
    cout << "Enter board width: ";
    cin >> width;
    cout << "Enter board height: ";
    cin >> height;
    world = new World(width, height);
}

void Gameplay::makeShout() {
    //TODO
    shout++;
}


void Gameplay::gameInfo() {
    system("cls");
    cout << R"(
 __        __   _                            _         _
 \ \      / /__| | ___ ___  _ __ ___   ___  | |_ ___  (_)_ __   __ _
  \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \ | | '_ \ / _` |
   \ V  V /  __/ | (_| (_) | | | | | |  __/ | ||  __/_| | | | | (_| |
    \_/\_/ \___|_|\___\___/|_| |_| |_|\___|  \__\___(_)_|_| |_|\__, |
                                                              |___/
    )" << "\n";

    cout << "\nWelcome to the Turn-Based World Simulator!\n\n";

    cout << "-> Each turn, all organisms perform their actions.\n";
    cout << "-> Animals move; plants stay in place.\n";
    cout << "-> Collisions result in combat – stronger wins (usually!).\n";
    cout << "-> Initiative and age decide who acts first.\n";
    cout << "-> In case of equal strength, the attacker wins.\n\n";

    cout << "YOU control: \033[1;34mThe Human\033[0m\n";
    cout << " - Move with arrow keys.\n";
    cout << " - Activate your special skill (5-turn duration, 5-turn cooldown).\n\n";

    cout << "The world is populated with various animals and plants.\n";
    cout << "Check the event log for battles, feeding, and more.\n\n";

    cout << "Good luck out there, pioneer of virtual evolution!\n";

    cout << "Press any key to start the game..." << endl;
}

void Gameplay::stats() {
    cout << "Statistics:" << endl;
    cout << "----------------" << endl;
    cout << "Shouts: " << shout << endl;
    cout << "-----------------" << endl;
}

void Gameplay::spawn(int number, OrganismType type) {
    for (int i = 0; i < number; i++) {
        Point position = world->getRandomFreeSpace();
        switch (type) {
            case OrganismType::Wolf:
                world->spawnOrganism(new Wolf(world, position, 1), position);
                break;
            case OrganismType::Sheep:
                world->spawnOrganism(new Sheep(world, position, 1), position);
                break;
            case OrganismType::Fox:
                world->spawnOrganism(new Fox(world, position, 1), position);
                break;
            case OrganismType::Turtle:
                world->spawnOrganism(new Turtle(world, position, 1), position);
                break;
            case OrganismType::Grass:
                world->spawnOrganism(new Grass(world, position, 1), position);
                break;
            case OrganismType::Dandelion:
                world->spawnOrganism(new Dandelion(world, position, 1), position);
                break;
            case OrganismType::Guarana:
                world->spawnOrganism(new Guarana(world, position, 1), position);
                break;
            case OrganismType::Nightshade:
                world->spawnOrganism(new Nightshade(world, position, 1), position);
                break;
            default:
                throw std::invalid_argument("Unknown organism type");
        }
    }
}

void Gameplay::spawnOrganisms() {
    Point playerPosition = Point(0, 0);
    world->spawnOrganism(new Human(world, 5, 4, playerPosition, "🧍", 1), playerPosition);
    spawn(2, OrganismType::Wolf);
    spawn(2, OrganismType::Sheep);
    spawn(2, OrganismType::Fox);
    spawn(2, OrganismType::Turtle);
    spawn(2, OrganismType::Grass);
    spawn(2, OrganismType::Dandelion);
    spawn(2, OrganismType::Guarana);
    spawn(2, OrganismType::Nightshade);
}

void Gameplay::getInput() {
    int key = _getch();

    if (key == 0 || key == 224) { 
        key = _getch();
    }

    input = key;
}

void Gameplay::handleInput() {
    switch (input) {
        case 'q':
            running = false;
            shout--;
            break;
        default:
            break;
    }
}

void Gameplay::endGame() {
    stats();

    std::cout << "Thanks for playing!\n";
    std::cout << "Press any key to exit...\n";

    input = _getch();
}