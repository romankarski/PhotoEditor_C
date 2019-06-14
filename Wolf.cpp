#include "Wolf.hpp"
#include "World.hpp"

Wolf::Wolf(int x, int y) : Animal(x, y)
{
    strength = 9;
    initiative = 5;
    sign = 'W';
    species = Species::WOLF;
    speciesText = "Wolf";
}

void Wolf::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        // reproduction
        Animal::collision(world, other_organism, reproduction_possible);

    }
}

Wolf* Wolf::createChild(const Point& position) const
{
    return new Wolf(position.x, position.y);
}