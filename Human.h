//
// Created by karol on 30.03.2025.
//

#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"


class Human : public Animal {
public:
    Human(const Point& position, World* world);
    Human(World* world, int strength, int initiative, Point& position, char symbol);
    ~Human();
    void action(char input) override;
};


#endif //HUMAN_H
