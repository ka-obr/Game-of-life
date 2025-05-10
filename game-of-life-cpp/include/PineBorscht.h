#ifndef PINEBORSCHT_H
#define PINEBORSCHT_H

#include "Plant.h"

class PineBorscht : public Plant {
public:
    PineBorscht(World* world, Point& position);
    PineBorscht(World* world, Point& position, int age);
    ~PineBorscht();
protected:
    void action() override;
    int collision(Organism& other) override;
};

#endif 