//
// Created by karol on 28.03.2025.
//

#include "World.h"

using namespace std;


World::World(int width, int height ) {
    organisms.resize(width);

    // wskazniki na tablice organizmow
    for (int i = 0; i < width; i++)
        organisms[i].resize(height);

    this->width = width;
    this->height = height;
}

World::~World() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (organisms[i][j] != nullptr) {
                delete organisms[i][j];
                organisms[i][j] = nullptr;
            }
        }
    }
    organisms.clear();
}

void World::update() {
    
}

void World::drawWorld(int width, int height) {
    system("cls");

    drawHorizontalBorder(width);

    for (int i = 0; i < height; i++) {
        std::cout << "# ";

        for (int j = 0; j < width; j++) {
            if (organisms[j][i] != nullptr) {
                std::cout << organisms[j][i]->getSymbol() << " ";
            }
            else {
                std::cout << "  ";
            }
        }

        std::cout << "# " << std::endl;
    }

    drawHorizontalBorder(width);
}

void World::move(const Point& position, const Point &destination) {
    if (destination.x < 0 || destination.x >= width || destination.y < 0 || destination.y >= height) {
        return; // out of bounds
    }
    organisms[destination.x][destination.y] = organisms[position.x][position.y];
    organisms[position.x][position.y] = nullptr;
}

void World::remove(const Point& position) {
    if (organisms[position.x][position.y] != nullptr) {
        delete organisms[position.x][position.y];
        organisms[position.x][position.y] = nullptr;
    }
}

bool World::isEmpty(const Point& position) {
    return organisms[position.x][position.y] == nullptr;
}

Point World::getRandomNeighbor(const Point& position) const {
    int randomNumber = rand() % 4;

    switch (randomNumber) {
        case 0:
            return Point(position.x, position.y - 1);
        case 1:
            return Point(position.x, position.y + 1);
        case 2:
            return Point(position.x - 1, position.y);
        case 3:
            return Point(position.x + 1, position.y);
        default:
            return Point(0, 0);
    }
}

void World::drawHorizontalBorder(int width) {
    for (int i = 0; i < width + 2; i++) {
        cout << "# ";
    }
    cout << endl;
}

void World::spawnOrganism(Organism* organism) {
    int x = rand() % WORLD_SIZE;
    int y = rand() % WORLD_SIZE;
    while (organisms[x][y] != nullptr) {
        x = rand() % WORLD_SIZE;
        y = rand() % WORLD_SIZE;
    }
    organisms[x][y] = organism;
    organisms[x][y]->getPosition().x = x;
    organisms[x][y]->getPosition().y = y;
}


void World::spawnOrganism(Organism* organism, const Point& position) {
    organisms[position.x][position.y] = organism;
    organisms[position.x][position.y]->getPosition().x = position.x;
    organisms[position.x][position.y]->getPosition().y = position.y;
}


void World::movePlayerUp() {
    move(playerPosition, Point(playerPosition.x, playerPosition.y - 1));
    if (playerPosition.y > 0)
        setPlayerPosition(playerPosition.x, playerPosition.y - 1);
}


void World::movePlayerDown() {
    move(playerPosition, Point(playerPosition.x, playerPosition.y + 1));
    
    if(playerPosition.y < height - 1)
        setPlayerPosition(playerPosition.x, playerPosition.y + 1);
}


void World::movePlayerLeft() {
    move(playerPosition, Point(playerPosition.x - 1, playerPosition.y));
    if (playerPosition.x > 0)
        setPlayerPosition(playerPosition.x - 1, playerPosition.y);
}


void World::movePlayerRight() {
    move(playerPosition, Point(playerPosition.x + 1, playerPosition.y));
    if (playerPosition.x < width - 1)
        setPlayerPosition(playerPosition.x + 1, playerPosition.y);
}

void World::printOrganismInfo(const Point& position) {
    // print organism info
    std::cout << "Organism info:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;

    std::cout << "Organism strength: " << organisms[position.x][position.y]->getStrength() << std::endl;
}


void World::printShoutSummary() {
    std::cout << std::endl;
    std::cout << "Shout actions summary:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;

    std::cout << "Human position: " << playerPosition.x << ", " << playerPosition.y << std::endl;

    // print organism info for human position
    if (organisms[playerPosition.x][playerPosition.y] != nullptr) {
        std::cout << "Organism info:" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << std::endl;

        printOrganismInfo(Point (playerPosition.x, playerPosition.y));
    }
}


void World::printStatistics() {
    // TODO

    std::cout << std::endl;
    std::cout << "World statistics:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;
}


Point World::getPlayerPosition() const {
    return playerPosition;
}


void World::setPlayerPosition(int x, int y) {
    playerPosition.x = x;
    playerPosition.y = y;
}


void World::setPlayerPosition(Point& position) {
    playerPosition = position;
}

