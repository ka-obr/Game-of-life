//
// Created by karol on 28.03.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H
#include "Organism.h"
#include "World.h"

class Animal : public Organism {
public:
    Animal(World* world, int strength, int initiative, const Point& position, string symbol);
    Animal(World* world, int strength, int initiative, const Point& position, string symbol, int age);
    ~Animal();

    void action() override;
    int collision(Organism& other) override;
protected:
    virtual void move(const Point& destination);
    virtual void eat(Organism& other);
    virtual void reproduce(Point& position);
    void die();

    virtual bool canKill(Organism& other) override;
    virtual bool canReproduce(const Organism& other, const Point& position) const;
    virtual bool haveSavedAttack(Organism& other);
    virtual void shouldReceiveStrength(Organism* plant, Organism* animal) override;
    virtual int escapeCollision(Organism& other) override;
    Animal* createAnimalByType(const Organism* parent, World* world, Point& position);

    virtual bool canEat(const Organism& other) const;

};



#endif //ANIMAL_H
