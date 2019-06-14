#ifndef __Grass__
#define __Grass__

#include "Plant.hpp"

class Grass : public Plant
{
    public:
        Grass(int x, int y);

        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Grass * createChild(const Point& position) const override;
};

#endif // define __Grass__