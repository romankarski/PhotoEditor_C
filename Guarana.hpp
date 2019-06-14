#ifndef __Guarana__
#define __Guarana__

#include "Plant.hpp"

class Guarana : public Plant
{
    public:
        Guarana(int x, int y);

        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Guarana * createChild(const Point& position) const override;
};

#endif // define __Guarana__