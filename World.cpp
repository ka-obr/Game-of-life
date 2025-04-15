//
// Created by karol on 28.03.2025.
//

#include "World.h"

using namespace std;


World::World(int width, int height ) {
    this->width = width;
    this->height = height;
}

World::~World() {
    organisms.clear();
}

void World::update(char input) {
    sort(organisms.begin(), organisms.end(), [](const Organism* a, const Organism* b) {
        if (a->getInitiative() == b->getInitiative()) {
            return a->getAge() > b->getAge();
        }
        return a->getInitiative() > b->getInitiative();
    });

    for (Organism* org : organisms) {
        org->action(input);
    }
}

void World::drawWorld(int width, int height) {
    system("cls");

    drawHorizontalBorder(width);

    for (int i = 0; i < height; i++) {
        std::cout << "# ";

        for (int j = 0; j < width; j++) {
            Organism* org = getAtCoordinates(Point(j, i));
            if (org != nullptr)
                std::cout << org->getSymbol() << ' ';
            else
                std::cout << "  ";
        }

        std::cout << "# " << std::endl;
    }

    drawHorizontalBorder(width);
}

void World::remove(const Point& position) {
    if (getAtCoordinates(position) == human)
        human = nullptr;
    
    for (auto it = organisms.begin(); it != organisms.end(); it++) {
        if ((*it)->getPosition() == position) {
            organisms.erase(it);
            return;
        }
    }
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

Organism* World::getAtCoordinates(Point cords) const {
    for (Organism* org : organisms) {
        if (org->getPosition() == cords) return org;
    }
    return nullptr;
}

bool World::isWithinBounds(const Point& position) const {
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}

Point World::getRandomFreeSpace() const {
    for(int i = 0; i < width * height; i++) {
        int x = rand() % width;
        int y = rand() % height;
        Point randomPoint(x, y);

        if(getAtCoordinates(randomPoint) == nullptr) {
            return randomPoint;
        }
    }

    return Point(-1, -1);

}

Point World::getRandomFreeSpaceAround(const Point& position) const {
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        Point neighbor(position.x + dx[i], position.y + dy[i]);

        if (isWithinBounds(neighbor) && getAtCoordinates(neighbor) == nullptr) {
            return neighbor; // Zwróć pierwsze wolne sąsiednie pole
        }
    }

    return Point(-1, -1);
}

void World::move(const Point& position, const Point &destination) {
    Organism* org = getAtCoordinates(position);
    if (org != nullptr && isWithinBounds(destination) && getAtCoordinates(destination) == nullptr) {
        org->setPosition(destination);
    }
}

void World::drawHorizontalBorder(int width) {
    for (int i = 0; i < width + 2; i++) {
        cout << "# ";
    }
    cout << endl;
}

void World::spawnOrganism(Organism* organism) {
    organisms.push_back(organism);
    organism->setPosition(Point(rand() % width, rand() % height));
}


void World::spawnOrganism(Organism* organism, const Point& position) {
    organisms.push_back(organism);
    organism->setPosition(position);
}

void World::printShoutSummary() {
    std::cout << std::endl;
    std::cout << "Shout actions summary:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;
}

void World::printHumanInfo() {
    std::cout << "Human - position: (" << human->getPosition().x <<
             ", " << human->getPosition().y <<
             ") strength: " << human->getStrength() <<  std::endl;
}

void World::printStatistics() {
    // TODO

    std::cout << std::endl;
    std::cout << "World statistics:" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;
}

Point World::getPlayerPosition() const {
    return human->getPosition();
}

int World::getHeight() {
    return height;
}

int World::getWidth() {
    return width;
}

void World::setHuman(Organism* org) {
    human = org;
}