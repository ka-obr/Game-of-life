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

void World::drawWorld(int height, int width) {
    system("cls");

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (organisms[i][j] != nullptr) {
                cout << organisms[i][j]->getSymbol();
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void World::move(Point position, Point destination) {
    organisms[destination.x][destination.y] = organisms[position.x][position.y];
    organisms[position.x][position.y] = nullptr;
}

void World::remove(Point position) {
    if (organisms[position.x][position.y] != nullptr) {
        delete organisms[position.x][position.y];
        organisms[position.x][position.y] = nullptr;
    }
}

bool World::isEmpty(Point position) {
    return organisms[position.x][position.y] == nullptr;
}

Point World::getRandomNeighbor(const Point& position) const {
    int randomNumber = rand() % 4;

    switch (randomNumber) {
        case 0:
            return Point(position.x - 1, position.y); // Up
        case 1:
            return Point(position.x + 1, position.y); // Down
        case 2:
            return Point(position.x, position.y - 1); // Left
        case 3:
            return Point(position.x, position.y + 1); // Right
        default:
            return Point(0, 0);
    }
}
