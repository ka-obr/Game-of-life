//
// Created by karol on 30.03.2025.
//

#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"


class Human : public Animal {
public:
    Human(const Point& position, World* world);
    Human(World* world, int strength, int initiative, Point& position, string symbol, int age);
    ~Human();
    void action(char input) override;
    void tryCollisionAndMove(Point destination);
};


#endif //HUMAN_H
