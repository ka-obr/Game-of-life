//
// Created by karol on 28.03.2025.
//

#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
#include "Point.h"


class World;

using namespace std;


class Organism {
protected:
    int strength;
    int initiative;
    Point position;
    int age;
    string symbol;
    World* world;
public:
    Organism(World* world);
    Organism(World* world, int strength, int initiative, Point position, string symbol);
    Organism(World* world, int strength, int initiative, Point position, string symbol, int age);
    ~Organism();

    virtual void action() = 0;
    virtual void action(char input);
    virtual int collision(Organism& other) = 0;
    virtual void die();
    virtual void reproduce(Point& position) = 0;
    virtual bool canKill(Organism& other) = 0;
    virtual void kill(Organism& other) const;

    int getStrength() const;
    int getInitiative() const;
    int getAge() const;
    string getSymbol() const;
    Point& getPosition();
    void setPosition(Point pos);
    void setAge(int age);
    void setStrength(int strenght);
};



#endif //ORGANISM_H
