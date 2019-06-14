#ifndef __Sheep__
#define __Sheep__

#include "Animal.hpp"

class Sheep : public Animal
{
    public:
        Sheep(int x, int y);

        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Sheep * createChild(const Point& position) const override;
};

#endif // define __Sheep__