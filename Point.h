//
// Created by karol on 28.03.2025.
//

#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point {
public:
        int x;
        int y;
        Point();
        Point(int x, int y);
        bool operator==(const Point& other) const;
        ~Point();
};


#endif //POINT_H
