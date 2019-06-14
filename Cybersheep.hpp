#ifndef __Cybersheep__
#define __Cybersheep__

#include "Animal.hpp"


class Cybersheep : public Animal
{
    public:
        Cybersheep(int x, int y);

        void action(World& world) override;
        Cybersheep * createChild(const Point& position) const override;
};

#endif // define __Cybersheep__