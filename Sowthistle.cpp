#include "Sowthistle.hpp"
#include "World.hpp"

Sowthistle::Sowthistle(int x, int y) : Plant(x, y)
{
    strength = 0;
    initiative = 0;
    sign = '.';
    species = Species::SOWTHISTLE;
    speciesText = "Sowthistle";
}

void Sowthistle::action(World& world){
    for( int i = 0; i < 3; ++i){
        // three tries for reproduction
        if ((double(rand()) / RAND_MAX) < 0.1 ){
            Point new_plant_position = takeNeighbouringPosition(world, false);
            if( new_plant_position != Point(-1,-1)){
                Organism* new_plant = createChild(new_plant_position);
                world.putOrganism(new_plant);

                char message[256];
                sprintf(message,"%s growing on (%d,%d)", speciesText.c_str(), new_plant_position.x, new_plant_position.y);
                world.takeEvent(message);

                break;
            }
        }
    }
}

void Sowthistle::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    // non
    death(world);
}

Sowthistle* Sowthistle::createChild(const Point& position) const
{
    return new Sowthistle(position.x, position.y);
}