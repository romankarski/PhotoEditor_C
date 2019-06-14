#ifndef __Animal__
#define __Animal__

#include "Organism.hpp"

class Animal : public Organism
{
    public:
        Animal(int x, int y);
        virtual ~Animal() = default;

        void action(World& world) override;
        void collision(World& world, Organism* other_organism, const bool reproduction_possible) override;
        void draw() const override;
        
    private:
        const int avg_lifetime;
        const int reproduction_age;
        const int infertility_period;

        int left_infertility_days;
};

#endif // define __Animal__