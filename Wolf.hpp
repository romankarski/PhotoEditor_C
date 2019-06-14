#ifndef __Wolf__
#define __Wolf__

#include "Animal.hpp"

class Wolf : public Animal
{
    public:
        Wolf(int x, int y);

        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Wolf * createChild(const Point& position) const override;
};

#endif // define __Wolf__