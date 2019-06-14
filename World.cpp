#include "World.hpp"
#include "mException.hpp"
#include <string>

World::World(const int world_size, const bool is_infinite)
    :min_size(5), is_infinite(is_infinite), current_turn(0)
{

    // checking size
    if(world_size < min_size){
        throw mException("Size couldn't be lower than" + std::to_string(world_size));
    }

    // resize table of organisms to sizexsize
    organisms.resize(world_size);
    for(auto& organism : organisms){
        organism.resize(world_size);
    }

    // starting organisms
    for(int i = 0; i < world_size; ++i){
        int choose = rand()%10;
        int x = rand()%world_size;
        int y = rand()%world_size;
        if(choose == 0) putOrganism<Grass>(x,y);
        else if(choose == 1) putOrganism<Sowthistle>(x,y);
        else if(choose == 2) putOrganism<Guarana>(x,y);
        else if(choose == 3) putOrganism<Deadly_nightshade>(x,y);
        else if(choose == 4) putOrganism<Heracleum_sosnowskyi>(x,y);
        else if(choose == 5) putOrganism<Wolf>(x,y);
        else if(choose == 6) putOrganism<Sheep>(x,y);
        else if(choose == 7) putOrganism<Fox>(x,y);
        else if(choose == 8) putOrganism<Turtle>(x,y);
        else if(choose == 9) putOrganism<Antelope>(x,y);

    }
    int x = rand()%world_size;
    int y = rand()%world_size;
    putOrganism<Human>(x,y);
    x = rand()%world_size;
    y = rand()%world_size;
    putOrganism<Cybersheep>(x,y);
    
}

void World::addOrganism(int x, int y, int choose){
    if(readOrganism(Point(x,y))){
        char message[256];
        sprintf(message,"\tCANNOT ADD ON (%d,%d)", x, y);
        takeEvent(message);
    }
    else{
        if(choose == 0) putOrganism<Grass>(x,y);
        else if(choose == 1) putOrganism<Sowthistle>(x,y);
        else if(choose == 2) putOrganism<Guarana>(x,y);
        else if(choose == 3) putOrganism<Deadly_nightshade>(x,y);
        else if(choose == 4) putOrganism<Heracleum_sosnowskyi>(x,y);
        else if(choose == 5) putOrganism<Wolf>(x,y);
        else if(choose == 6) putOrganism<Sheep>(x,y);
        else if(choose == 7) putOrganism<Fox>(x,y);
        else if(choose == 8) putOrganism<Turtle>(x,y);
        else if(choose == 9) putOrganism<Antelope>(x,y);
    }
}

void World::makeTurn()
{
    //change turn
    ++current_turn;
    
    // clear events
    events.clear();

    // sorting organisms
    std::vector<Organism*> sorted_organisms;
    sortOrganisms(sorted_organisms);

    // make Actions for each Organism
    for( const auto& organism : sorted_organisms){

        // in case of death one of organisms in collision
        if(organism && organism->isAlive()){
            organism->action(*this);
        }

    }

    // delete dead organisms
    deleteDeadOrganisms();

}

void World::drawWorld()
{
    for(const auto& row : organisms){
        for(const auto& organism : row){
            if(organism){
                organism->draw();
            }
            else{
                std::cout<<" ";
            }

            std::cout<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\nCurrent turn: "<<current_turn + 1<<"\n\n";

    std::cout<<"Events :\n";
    for(int i = 0; i < events.size(); ++i){
        std::cout<<"->"<<events[i]<<"\n";
        if(i < events.size()-1 && events[i][0]=='t' && events[i+1][0] !='\t'){
            std::cout<<"\n";
        }
    }
}

void World::putOrganism(Organism* organism)
{
    Point position = organism->readPosition();
    Organism* otherOrganism = organisms[position.x][position.y];

    if(otherOrganism && otherOrganism->isAlive()){
        // two organism on one position -> collision
        organism->collision(*this, otherOrganism);

        if(otherOrganism->readPosition() == position){
            otherOrganism->collision(*this,organism,false);
        }
    }
    else{
        organisms[position.x][position.y] = organism;
    }
}

void World::deleteOrganism(const Point& position)
{
    organisms[position.x][position.y] = nullptr;
}

void World::updatePosition(Organism* organism)
{
    deleteOrganism(organism->readPreviousPosition());
    putOrganism(organism);
}

void World::takeEvent(const std::string& message)
{
    events.push_back(message);
}

template<class TOrganism>

void World::putOrganism(int x, int y)
{
    organisms[x][y] = new TOrganism(x, y);
}

void World::sortOrganisms(std::vector<Organism*>& sorted_organisms) const
{
    for(const auto& row : organisms){
        for(const auto& organism : row){
            if(organism){
                sorted_organisms.push_back(organism);
            }
        }
    }

    std::sort(std::begin(sorted_organisms), std::end(sorted_organisms),
    [](const auto& o1, const auto& o2) {
			return *o1 > *o2;
	});
}

void World::deleteDeadOrganisms()
{
    for(auto& row : organisms){
        for(auto& organism : row){
            if(organism && !(organism->isAlive())){
                    delete organism;
                    organism = nullptr;
            }
        }
    }
}