 #include "Grass.hpp"
#include "World.hpp"

Grass::Grass(int x, int y) : Plant(x, y)
{
    strength = 0;
    initiative = 0;
    sign = ',';
    species = Species::GRASS;
    speciesText = "Grass";
}

void Grass::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    // non
    death(world);
}

Grass* Grass::createChild(const Point& position) const
{
    return new Grass(position.x, position.y);
}