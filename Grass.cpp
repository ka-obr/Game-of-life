#include "include/Grass.h"

Grass::Grass(World* world, Point& Position)
    : Plant(world, 0, position, "🌱", 0) {

}

Grass::Grass(World* world, Point& position, int age)
    : Plant(world, 0, position, "🌱", age) {

}

Grass::~Grass() {
    // Destructor implementation
}