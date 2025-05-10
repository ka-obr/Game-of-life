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
#include "include/PineBorscht.h"
#include "include/Antelope.h"
#include "include/SaveManager.h"
#include <conio.h>

using namespace std;

Gameplay::Gameplay() {
    running = true;
    input = ' ';
    shout = 0;
}

Gameplay::~Gameplay() {
    delete human;
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
    world->printHumanInfo();
    world->printShoutSummary();

    while (running) {
        getInput();
        if (handleInput()) {
            world->update(input);
            makeShout();
        }

        world->drawWorld(width, height);
        world->printHumanInfo();
        world->printShoutSummary();
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
    while (!(cin >> width) || width <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number for width: ";
    }

    cout << "Enter board height: ";
    while (!(cin >> height) || height <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number for height: ";
    }

    world = new World(width, height);
}

void Gameplay::makeShout() {
    shout++;
}


void Gameplay::gameInfo() {
    system("cls");
    cout << R"(
__        __   _                          
\ \      / /__| | ___ ___  _ __ ___   ___ 
 \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \
  \ V  V /  __/ | (_| (_) | | | | | |  __/
   \_/\_/ \___|_|\___\___/|_| |_| |_|\___|
  
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

    cout << "Good luck out there, pioneer of virtual evolution!\n\n";

    cout << "Controls:\n";
    cout << " - Arrows: Human movement.\n";
    cout << " - Q: Quit game.\n";
    cout << " - R: Human special ability.\n";
    cout << " - T: Make Shout.\n";
    cout << " - S: Save file.\n";
    cout << " - L: Load file.\n\n";

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
            case OrganismType::PineBorscht:
                world->spawnOrganism(new PineBorscht(world, position, 0), position);
                break;
            case OrganismType::Antelope:
                world->spawnOrganism(new Antelope(world, position, 1), position);
                break;
            default:
                throw std::invalid_argument("Unknown organism type");
        }
    }
}

void Gameplay::spawnOrganisms() {
    Point playerPosition = Point(0, 0);
    human = new Human(world, 5, 4, playerPosition, "🧍", 1);
    world->spawnOrganism(human, playerPosition);

    spawn(2, OrganismType::Wolf);
    spawn(2, OrganismType::Sheep);
    spawn(2, OrganismType::Fox);
    spawn(2, OrganismType::Turtle);
    spawn(2, OrganismType::Grass);
    spawn(2, OrganismType::Dandelion);
    spawn(2, OrganismType::Guarana);
    spawn(2, OrganismType::Nightshade);
    spawn(2, OrganismType::PineBorscht);
    spawn(2, OrganismType::Antelope);
}

void Gameplay::saveToFile(const std::string& filename) {
    SaveManager saveManager;
    saveManager.saveGame(filename, world, shout);

    std::string message = "Game saved to " + filename;
    world->addShoutSummaryMessage(message);
}


void Gameplay::loadFromFile(const std::string& filename) {
    SaveManager saveManager;
    shout = saveManager.loadGame(filename, world);
    width = world->getWidth();
    height = world->getHeight();

    human = dynamic_cast<Human*>(world->getHuman());

    std::string message = "Game loaded from " + filename;
    world->addShoutSummaryMessage(message);
}

void Gameplay::getInput() {
    int key;
    do {
        key = _getch();

        if (key == 0 || key == 224) { 
            key = _getch();
        }
    } while(allowedKeys.find(key) == allowedKeys.end());

    input = key;
}

void Gameplay::handleHumanSpecialAbility(Human* human) {
    if(!world->isHumanAlive()) {
        std::string message = "Human is dead!";
        world->addShoutSummaryMessage(message);
    }
    else if(human->getSpecialAbilityCooldown() > 0) {
        std::string message = "Human special ability is on cooldown for " + std::to_string(human->getSpecialAbilityCooldown()) + " turns!";
        world->addShoutSummaryMessage(message);
    } 
    else if(human->getSpecialAbilityActive()) {
        std::string message = "Human special ability is already active!";
        world->addShoutSummaryMessage(message);
    } 
    else if(human != nullptr) {
        human->setSpecialAbilityActive(true);
        std::string message = "Human special ability activated!!!";
        world->addShoutSummaryMessage(message);
    }
}

bool Gameplay::handleInput() {
    switch (input) {
        case 'q':
            running = false;
            return false;
        case 'r':
            handleHumanSpecialAbility(human);
            return false;
        case 's':
            saveToFile("save.json");
            return false;
        case 'l':
            loadFromFile("save.json");
            return false;
        default:
            return true; // Allow the game to continue
    }
}

void Gameplay::endGame() {
    stats();

    std::cout << "Thanks for playing!\n";
    std::cout << "Press any key to exit...\n";

    input = _getch();
}