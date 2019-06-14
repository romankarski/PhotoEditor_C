#ifndef __Sowthistle__
#define __Sowthistle__

#include "Plant.hpp"

class Sowthistle : public Plant
{
    public:
        Sowthistle(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Sowthistle * createChild(const Point& position) const override;
};

#endif // define __Sowthistle__