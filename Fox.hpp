#ifndef __Fox__
#define __Fox__

#include "Animal.hpp"

class Fox : public Animal
{
    public:
        Fox(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Fox * createChild(const Point& position) const override;
};

#endif // define __Fox__