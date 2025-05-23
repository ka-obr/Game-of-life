#include "include/SaveManager.h"
#include "include/World.h"
#include "include/Human.h"
#include "include/Wolf.h"
#include "include/Sheep.h"
#include "include/Fox.h"
#include "include/Turtle.h"
#include "include/Grass.h"
#include "include/Dandelion.h"
#include "include/Guarana.h"
#include "include/Nightshade.h"
#include "include/Antelope.h"
#include "include/PineBorscht.h"
#include <fstream>
#include <typeinfo>

using json = nlohmann::json;

void SaveManager::saveGame(const std::string& filename, World* world, int shout) {
    json saveData;

    saveData["world"]["width"] = world->getWidth();
    saveData["world"]["height"] = world->getHeight();
    saveData["world"]["shout"] = shout;

    saveData["organisms"] = json::array();
    for (const auto& organism : world->getOrganisms()) {
        json organismData;
        organismData["type"] = typeid(*organism).name();
        organismData["position"] = {organism->getPosition().x, organism->getPosition().y};
        organismData["strength"] = organism->getStrength();
        organismData["initiative"] = organism->getInitiative();
        organismData["age"] = organism->getAge();
        saveData["organisms"].push_back(organismData);

        Human* human = dynamic_cast<Human*>(organism);
        if (human != nullptr) {
            saveData["human"]["specialAbilityActive"] = human->getSpecialAbilityActive();
            saveData["human"]["specialAbilityCooldown"] = human->getSpecialAbilityCooldown();
            saveData["human"]["specialAbilityCounter"] = human->getSpecialAbilityCounter();
        }
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file for saving.");
    }
    file << saveData.dump(4);
    file.close();
}

int SaveManager::loadGame(const std::string& filename, World* world) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file for loading.");
    }

    json loadData;
    file >> loadData;
    file.close();

    int width = loadData["world"]["width"];
    int height = loadData["world"]["height"];
    int shout = loadData["world"]["shout"];

    World* newWorld = new World(width, height);

    json humanData = loadData.contains("human") ? loadData["human"] : json::object();

    for (const auto& organismData : loadData["organisms"]) {
        Organism* organism = createOrganismFromData(organismData, humanData, world);
        if (organism == nullptr) {
            continue;
        }
        int x = organismData["position"][0];
        int y = organismData["position"][1];
        Point position(x, y);
        newWorld->spawnOrganism(organism, position);
        Human* human = dynamic_cast<Human*>(organism);
        if (human != nullptr) 
            newWorld->setHuman(human);
    }

    *world = *newWorld;
    delete newWorld;
    return shout;
}

Organism* SaveManager::createOrganismFromData(const nlohmann::json& organismData, const nlohmann::json& humanData, World* world) {
    std::string type = organismData["type"];
    int x = organismData["position"][0];
    int y = organismData["position"][1];
    int strength = organismData["strength"];
    int initiative = organismData["initiative"];
    int age = organismData["age"];
    Point position(x, y);

    if (type == typeid(Human).name()) {
        int specialAbilityActive = humanData.value("specialAbilityActive", 0);
        int specialAbilityCooldown = humanData.value("specialAbilityCooldown", 0);
        int specialAbilityCounter = humanData.value("specialAbilityCounter", 0);

        if (humanData.contains("specialAbilityCooldown") && 
            humanData.contains("specialAbilityCounter")) {
            return new Human(world, strength, initiative, position, "🧍", age, specialAbilityActive, specialAbilityCooldown, specialAbilityCounter);
        } else {
            return new Human(world, strength, initiative, position, "🧍", age);
        }
        return new Human(world, strength, initiative, position, "🧍", age, specialAbilityActive, specialAbilityCooldown, specialAbilityCounter);
    } 
    if (type == typeid(Wolf).name()) {
        return new Wolf(world, position, age);
    } else if (type == typeid(Sheep).name()) {
        return new Sheep(world, position, age);
    } else if (type == typeid(Fox).name()) {
        return new Fox(world, position, age);
    } else if (type == typeid(Turtle).name()) {
        return new Turtle(world, position, age);
    } else if (type == typeid(Grass).name()) {
        return new Grass(world, position, age);
    } else if (type == typeid(Dandelion).name()) {
        return new Dandelion(world, position, age);
    } else if (type == typeid(Guarana).name()) {
        return new Guarana(world, position, age);
    } else if (type == typeid(Nightshade).name()) {
        return new Nightshade(world, position, age);
    } else if (type == typeid(PineBorscht).name()) {
        return new PineBorscht(world, position, age);
    } else if (type == typeid(Antelope).name()) {
        return new Antelope(world, position, age);
    }

    throw std::invalid_argument("Unknown organism type: " + type);
}
