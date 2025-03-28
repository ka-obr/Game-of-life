//
// Created by karol on 28.03.2025.
//

#include "Gameplay.h"

using namespace std;

Gameplay::Gameplay() {
    world = new World();
    running = true;
}

Gameplay::~Gameplay() {
    delete world;
}

void Gameplay::startGame() {
    cout << "Welcome to the game!" << endl;
    cout << "Press 'q' to quit." << endl;

    while (running) {
        world->drawWorld();
        world->makeShout();

        char command;
        cin >> command;
        if (command == 'q') {
            running = false;
            break;
        }

    }
}


