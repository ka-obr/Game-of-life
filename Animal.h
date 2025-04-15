//
// Created by karol on 28.03.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"
#include "World.h"

class Animal : public Organism {
public:
    Animal(World* world, int strength, int initiative, const Point& position, char symbol);
    Animal(World* world, int strength, int initiative, const Point& position, char symbol, int age);
    ~Animal();

    void action() override;
    bool collision(Organism& other) override;
protected:
    void move(const Point& destination);
    void eat(Organism& other);
    void reproduce(Point& position);

    bool canMoveTo(const Point& position) const;
    bool canEat(const Organism& other) const;

};



#endif //ANIMAL_H
