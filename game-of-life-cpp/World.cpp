//
// Created by karol on 28.03.2025.
//

#include "include/World.h"
#include "include/Animal.h"

using namespace std;


World::World(int width, int height ) {
    this->width = width;
    this->height = height;
    human = nullptr;
    i = 0;
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

    for (Organism* organism : organisms) {
        organism->setHasActed(false);
    }

    for (i = 0; i < organisms.size(); i++) {
        organisms[i]->action(input);
    }
}

void World::drawWorld(int width, int height) {
    system("cls");

    drawHorizontalBorder(width);

    for (int i = 0; i < height; i++) {
        std::cout << "#";

        for (int j = 0; j < width; j++) {
            Organism* org = getAtCoordinates(Point(j, i));
            if (org != nullptr)
                std::cout << org->getSymbol();
            else
                std::cout << "  ";
        }

        std::cout << " # " << std::endl;
    }

    drawHorizontalBorder(width);
}

void World::remove(const Point& position) {
    if (getAtCoordinates(position) == human) {
        human = nullptr;
    }
    
    for (auto it = organisms.begin(); it != organisms.end(); it++) {
        if ((*it)->getPosition() == position) {
            if (distance(organisms.begin(), it) <= i) {
                i--;
            }
            organisms.erase(it);
            return;
        }
    }
}

Point World::getRandomNeighbor(const Point& position) const {
    std::vector<vector<int>> displaces = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    std::random_device rd;
    std::default_random_engine rng(rd());

    std::shuffle(displaces.begin(), displaces.end(), rng);

    for (vector<int> displace : displaces) {
        Point neighbor(position.x + displace[0], position.y + displace[1]);

        if (isWithinBounds(neighbor)) {
            return neighbor; // Zwróć pierwsze wolne sąsiednie pole
        }
    }
    
    return Point(-1, -1);
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

bool World::isHumanAlive() const {
    for (const auto& organism : organisms) {
        if (organism == human) {
            return true;
        }
    }
    return false;
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

void World::killNeighbors(Point& position, int type) {
    // type = 1 - animals, type = 0 - everything
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        Point neighbor(position.x + dx[i], position.y + dy[i]);
        Organism* killer = getAtCoordinates(position);

        if (isWithinBounds(neighbor)) {
            Organism* other = getAtCoordinates(neighbor);
            if (other != nullptr) {
                if (type == 1 && dynamic_cast<Animal*>(other) != nullptr) {
                    killer->kill(*other);
                } else if (type == 0) {
                    killer->kill(*other);
                }
            }
        }
    }
}

Point World::getRandomFreeSpaceAround(const Point& position) const {
    std::vector<int> dx = {0, 1, -1};
    std::vector<int> dy = {0, 1, -1};

    std::random_device rd;
    std::default_random_engine rng(rd());

    std::shuffle(dx.begin(), dx.end(), rng);
    std::shuffle(dy.begin(), dy.end(), rng);

    for (int x : dx) {
        for (int y : dy) {
            Point neighbor(position.x + x, position.y + y);

            if (isWithinBounds(neighbor) && getAtCoordinates(neighbor) == nullptr) {
                return neighbor; // Zwróć pierwsze wolne sąsiednie pole
            }

        }
    }
    
    return Point(-1, -1);
}

Point World::findSafeSpaceAround(Point& position) const {
    std::vector<vector<int>> displaces = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    std::random_device rd;
    std::default_random_engine rng(rd());

    std::shuffle(displaces.begin(), displaces.end(), rng);

    Organism* org = getAtCoordinates(position);

    for (vector<int> displace : displaces) {
        Point neighbor(position.x + displace[0], position.y + displace[1]);

        Organism* other = getAtCoordinates(neighbor);
        if (other != nullptr && other->getStrength() > org->getStrength()) {
            continue; // Skip if the neighbor is stronger
        }

        if (isWithinBounds(neighbor)) {
            return neighbor;
        }
    }
    return position;
}

bool World::hasFreeSpaceAround(Point position) {
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        Point neighbor(position.x + dx[i], position.y + dy[i]);

        if (isWithinBounds(neighbor) && getAtCoordinates(neighbor) == nullptr) {
            return true;
        }
    }

    return false;
}

Point World::getRandomSpaceDoubleMove(const Point& position) const {
    std::vector<std::pair<int, int>> displacements = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, // Single moves
        {0, 2}, {0, -2}, {2, 0}, {-2, 0}  // Double moves
    };

    std::random_device rd;
    std::default_random_engine rng(rd());

    std::shuffle(displacements.begin(), displacements.end(), rng);

    for (const auto& displacement : displacements) {
        Point neighbor(position.x + displacement.first, position.y + displacement.second);

        if (isWithinBounds(neighbor)) {
            return neighbor;
        }
    }

    return position;
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

void World::addShoutSummaryMessage(const std::string& message) {
    shoutSummaryMessages.push_back(message);
}

void World::printShoutSummaryMessages() {
    int messageCount = shoutSummaryMessages.size() > 10 ? 10 : shoutSummaryMessages.size();

    for(int i = 0; i < messageCount; i++) {
        std::cout << shoutSummaryMessages[i] << std::endl;
    }
    shoutSummaryMessages.clear();
}

void World::printShoutSummary() {
    std::cout << std::endl;
    std::cout << "Shout actions summary:" << std::endl;
    std::cout << "----------------" << std::endl;
    
    printShoutSummaryMessages();
}

void World::printHumanInfo() {
    if (human != nullptr) {
        std::cout << "Human - position: (" << human->getPosition().x <<
        ", " << human->getPosition().y <<
        ") strength: " << human->getStrength() <<  std::endl;
    }
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

Organism* World::getHuman() const {
    return human;
}
std::vector<Organism*>& World::getOrganisms() {
    return organisms;
}