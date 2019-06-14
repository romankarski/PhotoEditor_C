#include "Deadly_nightshade.hpp"
#include "World.hpp"

Deadly_nightshade::Deadly_nightshade(int x, int y) : Plant(x, y)
{
    strength = 99;
    initiative = 0;
    sign = '?';
    species = Species::DEADLY_NIGHTSHADE;
    speciesText = "Deadly_nightshade";
}

void Deadly_nightshade::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(other_organism && !other_organism->isFlora() && other_organism->isAlive()){
        // kill animal
        other_organism->death(world);
        death(world);

        char message[256];
        sprintf(message,"\t%s eats %s and die (%d,%d)", other_organism->readSpeciesText().c_str(),speciesText.c_str(), position.x, position.y);
        world.takeEvent(message);
    }

}

Deadly_nightshade* Deadly_nightshade::createChild(const Point& position) const
{
    return new Deadly_nightshade(position.x, position.y);
}