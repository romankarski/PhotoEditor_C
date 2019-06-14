#include "Turtle.hpp"
#include "World.hpp"
#include "mException.hpp"

Turtle::Turtle(int x, int y) : Animal(x, y)
{
    strength = 2;
    initiative = 1;
    sign = 'T';
    species = Species::TURTLE;
    speciesText = "Turtle";
}

void Turtle::action(World& world){

    //movement
    previous_position = position;
    try{
        if((double(rand())/RAND_MAX) < 0.25){
            //only change possition in 25% of events
            position = takeNeighbouringPosition(world);

            char message[256];
            sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
            world.takeEvent(message);

            world.updatePosition(this);

        } 
    }
    catch(mException mexception){

        std::cout<<"Turtle_action_ "<<mexception.text;
    }

}

void Turtle::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        // reproduction
        Animal::collision(world, other_organism, reproduction_possible);

    }
}

Turtle* Turtle::createChild(const Point& position) const
{
    return new Turtle(position.x, position.y);
}