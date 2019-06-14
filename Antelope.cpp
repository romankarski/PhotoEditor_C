#include "Antelope.hpp"
#include "World.hpp"
#include "mException.hpp"

Antelope::Antelope(int x, int y) : Animal(x, y)
{
    strength = 4;
    initiative = 4;
    sign = 'A';
    species = Species::ANTELOPE;
    speciesText = "Antelope";
}

void Antelope::action(World& world){

    //movement
    previous_position = position;
    Point pos;
    try{
            // move 2 fields
            position = takeNeighbouringPosition(world);
            do{
                pos = takeNeighbouringPosition(world);
            }while(pos == previous_position);

            position = pos;

            char message[256];
            sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
            world.takeEvent(message);

            world.updatePosition(this);
    }
    catch(mException mexception){

        std::cout<<"antelope_action_ "<<mexception.text;
    }

}

void Antelope::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        // reproduction
        Animal::collision(world, other_organism, reproduction_possible);

    }
}

Antelope* Antelope::createChild(const Point& position) const
{
    return new Antelope(position.x, position.y);
}