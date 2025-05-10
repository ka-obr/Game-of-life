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
    Human(World* world, int strength, int initiative, Point& position, string symbol, int age, int specialAbilityActive, int specialAbilityCooldown, int specialAbilityCounter);
    ~Human();
    void action(char input) override;
    void tryCollisionAndMove(Point destination);

    bool getSpecialAbilityActive() const;
    void setSpecialAbilityActive(bool specialAbilityActive);

    int getSpecialAbilityCooldown() const;
    int getSpecialAbilityCounter() const;

private:
    bool specialAbilityActive;
    int specialAbilityCooldown;
    int specialAbilityCounter;
};


#endif //HUMAN_H
