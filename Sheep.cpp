#include "Sheep.hpp"
#include "World.hpp"

Sheep::Sheep(int x, int y) : Animal(x, y)
{
    strength = 4;
    initiative = 4;
    sign = 'S';
    species = Species::SHEEP;
    speciesText = "Sheep";
}

void Sheep::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        // reproduction
        Animal::collision(world, other_organism, reproduction_possible);


    }
}

Sheep* Sheep::createChild(const Point& position) const
{
    return new Sheep(position.x, position.y);
}