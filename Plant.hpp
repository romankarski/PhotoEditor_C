#ifndef __Plant__
#define __Plant__

#include "Organism.hpp"

class Plant : public Organism
{
    public:
        Plant(int x, int y);
        virtual ~Plant() = default;

        void action(World& world) override;
        void draw() const override;
        
    private:
        const int avg_lifetime;
};

#endif // define __Plant__