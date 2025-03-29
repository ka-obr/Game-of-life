//
// Created by karol on 28.03.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"
#include "World.h"

class Animal : public Organism {
public:
    Animal(World& world, int strength, int initiative, Point& position, char symbol);
    virtual ~Animal() override;

    virtual void action() override;
    virtual bool collision(Organism& other) override;
    //virtual void draw() override;

protected:
    virtual void move(const Point& destination);
    virtual void eat(Organism& other);
    virtual void reproduce(Point& position);

    virtual bool canMoveTo(const Point& position) const;
    virtual bool canEat(const Organism& other) const;

};



#endif //ANIMAL_H
