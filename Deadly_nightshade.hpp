#ifndef __Deadly_nightshade__
#define __Deadly_nightshade__

#include "Plant.hpp"

class Deadly_nightshade : public Plant
{
    public:
        Deadly_nightshade(int x, int y);

        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Deadly_nightshade * createChild(const Point& position) const override;
};

#endif // define __Deadly_nightshade__