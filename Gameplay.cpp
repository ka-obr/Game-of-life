//
// Created by karol on 28.03.2025.
//

#include "Gameplay.h"
#include "Human.h"
#include "Wolf.h"
#include "Sheep.h"
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


void Gameplay::spawnWolves(int number) {
    for (int i = 0; i < number; i++) {
        Point wolfPosition = world->getRandomFreeSpace();
        world->spawnOrganism(new Wolf(world, wolfPosition), wolfPosition);
    }
}

void Gameplay::spawnSheep(int number) {
    for (int i = 0; i < number; i++) {
        Point sheepPosition = world->getRandomFreeSpace();
        world->spawnOrganism(new Sheep(world, sheepPosition), sheepPosition);
    }
}

void Gameplay::spawnOrganisms() {
    Point playerPosition = Point(0, 0);
    world->spawnOrganism(new Human(world, 5, 4, playerPosition, 'H'), playerPosition);
    spawnWolves(2);
    spawnSheep(2);
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
    world->printStatistics();

    std::cout << "Thanks for playing!\n";
    std::cout << "Press any key to exit...\n";

    input = _getch();
}










