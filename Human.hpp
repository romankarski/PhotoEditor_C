#ifndef __Human__
#define __Human__

#include "Animal.hpp"

class Human : public Animal
{
    public:
        Human(int x, int y);

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        void death(World& world) override;
        Human * createChild(const Point& position) const override;
    private:
        int left_turns_period;
        int left_turns_break;
        int previous_turn;
};

#endif // define __Human__
