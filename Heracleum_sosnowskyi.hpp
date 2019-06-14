#ifndef __Heracleum_sosnowskyi__
#define __Heracleum_sosnowskyi__

#include "Plant.hpp"

class Heracleum_sosnowskyi : public Plant
{
    public:
        Heracleum_sosnowskyi(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        Heracleum_sosnowskyi * createChild(const Point& position) const override;
};

#endif // define __Heracleum_sosnowskyi__