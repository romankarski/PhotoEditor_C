#include "Plant.hpp"
#include "World.hpp"
#include "mException.hpp"
#include <string>

Plant::Plant(int x, int y)
    : Organism(x, y), avg_lifetime(250)
{

}

void Plant::action(World& world)
{
    ++age;

    // plant death
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

    // growing
    if((double(rand())/RAND_MAX) < 0.1){
        // 10% chance for growing
        try
        {
            Point new_plant_position = takeNeighbouringPosition(world, false);
            if(new_plant_position != Point(-1,-1)){
                char message[256];
                sprintf(message,"\t%s is growing on (%d,%d)",speciesText.c_str(),new_plant_position.x, new_plant_position.y);
                world.takeEvent(message);

                Organism* new_plant = createChild(new_plant_position);
                world.putOrganism(new_plant);
            }
        }
        catch(mException mexception)
        {
            std::cerr <<"plant_grow_ "<< mexception.text;
        }
    }   

}

void Plant::draw() const
{
    std::cout << sign;
}