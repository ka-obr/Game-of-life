#include "include/Wolf.h"

Wolf::Wolf(World* world, Point& position)
    : Animal(world, 9, 5, position, "🐺") {
}

Wolf::Wolf(World* world, Point& position, int age)
    : Animal(world, 9, 5, position, "🐺", age) {
}

Wolf::~Wolf() {

}