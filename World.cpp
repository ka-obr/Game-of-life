//
// Created by karol on 28.03.2025.
//

#include "World.h"

using namespace std;


World::World() {
    for (int i = 0; i < WORLD_SIZE; ++i) {
        for (int j = 0; j < WORLD_SIZE; ++j) {
            organisms[i][j] = nullptr;
        }
    }
}

World::~World() {
    for (int i = 0; i < WORLD_SIZE; ++i) {
        for (int j = 0; j < WORLD_SIZE; ++j) {
            if (organisms[i][j] != nullptr)
                delete organisms[i][j];
        }
    }
}

void World::makeShout() {
    // Implementation of makeShout TODO
}

void World::drawWorld() {
    system("cls");

    for (int i = 0; i < WORLD_SIZE; ++i) {
        for (int j = 0; j < WORLD_SIZE; ++j) {
            if (organisms[i][j] != nullptr) {
                cout << organisms[i][j]->getSymbol();
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}
