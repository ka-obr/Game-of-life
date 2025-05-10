#ifndef SAVEMANAGER__H
#define SAVEMANAGER_H

#include <string>
#include "World.h"
#include "../nlohmann/json.hpp"

class SaveManager {
private:
    Organism* createOrganismFromData(const nlohmann::json& organismData, const nlohmann::json& humanData, World* world);
public:
    void saveGame(const std::string& filename, World* world, int shout);
    int loadGame(const std::string& filename, World* world);
};

#endif
