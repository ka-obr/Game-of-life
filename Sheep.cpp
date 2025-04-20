#include "include/Sheep.h"

Sheep::Sheep(World* world, Point& position)
    : Animal(world, 4, 4, position, "🐑") {
    // Constructor implementation
}

Sheep::Sheep(World* world, Point& position, int age)
    : Animal(world, 4, 4, position, "🐑", age) {
    // Constructor implementation
}

Sheep::~Sheep() {
    // Destructor implementation
}