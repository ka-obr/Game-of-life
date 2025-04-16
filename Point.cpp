//
// Created by karol on 28.03.2025.
//

#include "include/Point.h"

Point ::Point() : x(0), y(0) {

}

Point::Point(int x, int y) : x(x), y(y) {

}

Point::~Point() {
    // Destructor implementation (if needed)
}

bool Point::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}
