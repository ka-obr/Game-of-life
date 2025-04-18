//
// Created by karol on 29.03.2025.
//

#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"
#include "World.h"



class Plant : public Organism {
public:
    Plant(World* world, const Point& position, string symbol);
    Plant(World* world, int strength, const Point& position, string symbol, int age);
    Plant(World* world, int strength, string symbol);

    virtual ~Plant();

    virtual void action() override;
    virtual int collision(Organism& other) override;
    virtual void die() override;
    virtual void kill(Organism& other) const override;
    virtual bool canKill(const Organism& other) const override;

    virtual bool hasFreeSpace() const;
    virtual bool canReproduceThisTurn() const;

protected:
    virtual void reproduce(Point& position) override;

};



#endif //PLANT_H
