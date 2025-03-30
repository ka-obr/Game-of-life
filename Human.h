//
// Created by karol on 30.03.2025.
//

#ifndef HUMAN_H
#define HUMAN_H
#include "Animal.h"


class Human : public Animal {
private:
    void move(const Point& position);
    void eat(Organism& other);
    void reproduce(Point& position);

    bool canMoveTo(const Point& position) const;
    bool canEat(const Organism& other) const;
public:
    Human(const Point& position, World& world);
    Human(World& world, int strength, int initiative, Point& position, char symbol);
    virtual ~Human();
    virtual void action() override;
    virtual bool collision(Organism& other) override;
    virtual void draw() override;
};



#endif //HUMAN_H
