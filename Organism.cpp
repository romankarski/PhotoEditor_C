#include "Organism.hpp"
#include "World.hpp"
#include "mException.hpp"
#include <string>

Organism::Organism(int x, int y)
    : position(x, y), previous_position(position), alive(true), age(0)
{

}

bool Organism::operator > (const Organism& other)
{
    if (initiative == other.initiative){
        return age > other.age;
    }
    return initiative > other.initiative;
}


Point Organism::takeNeighbouringPosition(World& world, const bool is_taken_position, const Point* to_avoid) const
{
    try{
        int world_size = world.readSize();
        std::vector<Point> neighbour_positions;
    
        for(int i = -1; i <= 1; ++i){

            for(int j = -1; j <= 1; ++j){

                // not consider a field aready taken by organism
                if( i != 0 || j != 0){

                    Point neighbour_position(position.x + i, position.y + j);

                    // Infinite wolrd means that there is no borders
                    if(!world.isInfinite()){
                        if(neighbour_position.x < 0 || neighbour_position.x >= world_size || neighbour_position.y < 0 || neighbour_position.y >= world_size){
                            continue;
                        }
                    }
                    else{
                        neighbour_position.x %= world_size;
                        neighbour_position.y %= world_size;

                        if(neighbour_position.x < 0) neighbour_position.x += world_size;
                        if(neighbour_position.y < 0) neighbour_position.y += world_size;
                    }

                    if(!is_taken_position && world.readOrganism(neighbour_position)){
                        // dont consider taken position
                        continue;
                    }

                    neighbour_positions.push_back(neighbour_position);
                }
            }
        }


        if(neighbour_positions.size() > 0){
            return neighbour_positions[rand() % neighbour_positions.size()];
        }

        if(neighbour_positions.size() == 0){
            return Point(-1,-1);
        }
    }
    catch(mException mexception){

        std::cout<<"\ntakeNeighbouringPosition_ "<<mexception.text;
    }

    throw mException("You SHOUDL NOT be here.\n");

}