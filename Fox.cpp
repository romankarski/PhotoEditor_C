#include "Fox.hpp"
#include "World.hpp"
#include "mException.hpp"

Fox::Fox(int x, int y) : Animal(x, y)
{
    strength = 3;
    initiative = 7;
    sign = 'F';
    species = Species::FOX;
    speciesText = "Fox";
}

void Fox::action(World& world){
        //movement
    previous_position = position;
    Point new_position;

    try{
            
        while(true){
            new_position = takeNeighbouringPosition(world);
            if(world.readOrganism(new_position)){
                if(world.readOrganism(new_position)->getStrength() > strength) continue;
                else break;
            }
            else break;
        }
        position = new_position;
        char message[256];
        sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
        world.takeEvent(message);

        world.updatePosition(this);

    }
    catch(mException mexception){

        std::cout<<"fox_action_ "<<mexception.text;
    }
}

void Fox::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        // reproduction
        Animal::collision(world, other_organism, reproduction_possible);

    }
}

Fox* Fox::createChild(const Point& position) const
{
    return new Fox(position.x, position.y);
}