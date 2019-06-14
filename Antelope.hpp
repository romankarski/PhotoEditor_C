#ifndef __Antelope__
#define __Antelope__

#include "Animal.hpp"

class Antelope : public Animal
{
    public:
        Antelope(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Antelope * createChild(const Point& position) const override;
};

#endif // define __Antelope__