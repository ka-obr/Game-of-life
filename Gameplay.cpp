//
// Created by karol on 28.03.2025.
//

#include "Gameplay.h"
#include <conio.h>

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
    cout << "Set width and height of the world: " << endl;
    int width, height;
    cin >> width;
    cin >> height;
    cout << "Press 'q' to quit." << endl;

    while (running) {
        world->drawWorld(height, width);
        world->makeShout();

        char command = _getch();
        if (command == 'q') {
            running = false;
            break;
        }

    }
}


