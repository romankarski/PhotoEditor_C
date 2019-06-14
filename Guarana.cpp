#include "Guarana.hpp"
#include "World.hpp"

Guarana::Guarana(int x, int y) : Plant(x, y)
{
    strength = 0;
    initiative = 0;
    sign = 'g';
    species = Species::GUARANA;
    speciesText = "Guarana";
}

void Guarana::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(other_organism && !other_organism->isFlora() && other_organism->isAlive()){
        // increse strength this animal by 3
        other_organism->increaseStrength(3);
        death(world);

        char message[256];
        sprintf(message,"\t%s eats %s and increase strength by 3 (%d,%d)", other_organism->readSpeciesText().c_str(),speciesText.c_str(), position.x, position.y);
        world.takeEvent(message);
    }

}

Guarana* Guarana::createChild(const Point& position) const
{
    return new Guarana(position.x, position.y);
}