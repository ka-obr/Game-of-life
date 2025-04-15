//
// Created by karol on 29.03.2025.
//

#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"
#include "World.h"



class Plant : public Organism {
private:
    static const int initiative = 0;
public:
    Plant(World* world, const Point& position, char symbol);
    Plant(World* world, int strength, const Point& position, char symbol);
    Plant(World* world, int strength, char symbol);

    virtual ~Plant();

    virtual void action() override;
    virtual bool collision(Organism& other) override;
    virtual void die() override;

    virtual bool hasFreeSpace() const;
    virtual bool canReproduce() const;

protected:
    virtual void reproduce(Point& position) override;

};



#endif //PLANT_H
