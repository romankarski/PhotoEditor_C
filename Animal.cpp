#include "Animal.hpp"
#include "World.hpp"
#include "mException.hpp"
#include <string>

Animal::Animal(int x, int y)
    : Organism(x , y), avg_lifetime(150), reproduction_age(10), infertility_period(15)
{
    left_infertility_days = 0;
}

void Animal::action(World& world)
{
    ++age;

    // death for age
    if(age >= avg_lifetime){
        double death_possibility = (age - avg_lifetime) / 25.0;
        if((double(rand()) / RAND_MAX) < death_possibility){
            char message[256];
            sprintf(message, "\t%s death for age (%d dni)", speciesText.c_str(),age);
            world.takeEvent(message);

            death(world);
            return;
        }
    }

    // Infertility
    if(left_infertility_days >0)
    {
        left_infertility_days--;
    }

    //movement
    previous_position = position;

    try{

        position = takeNeighbouringPosition(world);
        if(position == Point(-1,-1)){
            position = previous_position;
            char message[256];
            sprintf(message, "%s cannot move",speciesText.c_str());
            world.takeEvent(message);
        }
        else{
            char message[256];
            sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
            world.takeEvent(message);

            world.updatePosition(this);
        }

    }
    catch(mException mexception){

        std::cout<<"action_movement_ "<<mexception.text;
    }

}

void Animal::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(!alive){
        return;
    }

    Species other_organism_species = other_organism->getSpecies();
    if(reproduction_possible && species == other_organism_species){
        // in case of reproduction

        position = previous_position;

        if( age >= reproduction_age && !left_infertility_days)
        {
            // breaktime in reproduction

            left_infertility_days = infertility_period;
            // position for child
            bool is_taken_position = false;
            Point child_position = takeNeighbouringPosition(world, is_taken_position);

            //point -1,-1 is point out of table it means that is no free field
            if(child_position != Point(-1,-1)){
                Organism* child = createChild(child_position);
                world.putOrganism(child);

                char message[256];
                sprintf(message, "\t%s make reproduction (%d,%d)",speciesText.c_str(), child_position.x, child_position.y);
                world.takeEvent(message);
            }

            else{

            }
        }

        world.updatePosition(this);
    }

    //fight
    
    if(species != other_organism_species && position == other_organism->readPosition()){
        int other_organism_strength = other_organism->getStrength();
        if(strength >= other_organism_strength){
            //Win

            other_organism->death(world);

            char message[256];
            sprintf(message,"\t%s win with %s (%d,%d)",speciesText.c_str(), other_organism->readSpeciesText().c_str() , position.x, position.y);
            world.takeEvent(message);
            world.putOrganism(this);
        }
        else{
            //Lose

            death(world);

            char message[256];
            sprintf(message,"\t%s has been defeated by %s (%d,%d)",speciesText.c_str(), other_organism->readSpeciesText().c_str() , position.x, position.y);
            world.takeEvent(message);
        }
    }

    if(other_organism_species >= GRASS){
        other_organism->death(world);
    }

    if(other_organism_species == TURTLE && strength < 5){
        char message[256];
        sprintf(message, "\t%s blocked %s (%d,%d)",other_organism->readSpeciesText().c_str(),speciesText.c_str(), position.x, position.y);
        world.takeEvent(message);

        position = previous_position;
        world.updatePosition(this);
    }
}

void Animal::draw() const
{
    std::cout<<sign;
}