#ifndef __Turtle__
#define __Turtle__

#include "Animal.hpp"

class Turtle : public Animal
{
    public:
        Turtle(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Turtle * createChild(const Point& position) const override;
};

#endif // define __Turtle__