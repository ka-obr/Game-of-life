#ifndef SAVEMANAGER__H
#define SAVEMANAGER_H

#include <string>
#include "World.h"
#include "../nlohmann/json.hpp"

class SaveManager {
public:
    void saveGame(const std::string& filename, World* world, int shout);
    int loadGame(const std::string& filename, World* world);
private:
    Organism* createOrganismFromData(const nlohmann::json& organismData, World* world);
};

#endif
