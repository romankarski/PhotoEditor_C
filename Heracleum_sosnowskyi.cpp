#include "Heracleum_sosnowskyi.hpp"
#include "World.hpp"

Heracleum_sosnowskyi::Heracleum_sosnowskyi(int x, int y) : Plant(x, y)
{
    strength = 10;
    initiative = 0;
    sign = '!';
    species = Species::HERACLEUM_SOSNOWSKYI;
    speciesText = "Heracleum_sosnowskyi";
}

void Heracleum_sosnowskyi::action(World& world){
    Plant::action(world);

    // killing everything around
    int world_size = world.readSize();
    std::vector<Point> neighbour_positions;
  
    for(int i = -1; i <= 1; ++i){

        for(int j = -1; j <= 1; ++j){

            // not consider a field aready taken by organism
            if( i != 0 || j != 0){

                Point neighbour_position(position.x + i, position.y + j);

                // Infinite world means that there is no borders
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

                neighbour_positions.push_back(neighbour_position);
            }
        }
    }

    for( auto& neighbour_position : neighbour_positions){
        Organism* neighbour = world.readOrganism(neighbour_position);
        if(neighbour && neighbour->isAlive()){
            Species other_organism_species = neighbour->getSpecies();
            if(other_organism_species < GRASS){
                if(other_organism_species == Species(CYBERSHEEP)){
                    continue;
                }
                else{
                    neighbour->death(world);
                    char message[256];
                    sprintf(message,"\t%s is SuPeR and kill %s on (%d,%d)", speciesText.c_str(), neighbour->readSpeciesText().c_str(), position.x, position.y);
                    world.takeEvent(message);
                }
            }
        }
    }

}

void Heracleum_sosnowskyi::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(other_organism->getSpecies() == Species(CYBERSHEEP)){

        char message[256];
        sprintf(message,"\t%s eats %s on (%d,%d)", other_organism->readSpeciesText().c_str(),speciesText.c_str(), position.x, position.y);
        world.takeEvent(message);

        death(world);

    }
    else if(other_organism && !other_organism->isFlora() && other_organism->isAlive()){
        // kill animal
        other_organism->death(world);
        death(world);

        char message[256];
        sprintf(message,"\t%s eats %s and die (%d,%d)", other_organism->readSpeciesText().c_str(),speciesText.c_str(), position.x, position.y);
        world.takeEvent(message);
    }

}

Heracleum_sosnowskyi* Heracleum_sosnowskyi::createChild(const Point& position) const
{
    return new Heracleum_sosnowskyi(position.x, position.y);
}