#include "Cybersheep.hpp"
#include "World.hpp"
#include "mException.hpp"

#include <utility>
#include <vector>
#include <math.h>

Cybersheep::Cybersheep(int x, int y) : Animal(x, y)
{
    strength = 4;
    initiative = 4;
    sign = 'C';
    species = Species::CYBERSHEEP;
    speciesText = "Cybersheep";
}

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

bool sortbysec(const std::pair<Point,float> &a, const std::pair<Point,float> &b){
    return (a.second < b.second);
}

void Cybersheep::action(World& world){
    try{
        int k = -1;
        int a,b;
        float distance;
        std::vector<std::pair<Point,float>> queue;
        for(int i = 0; i < world.readSize(); i++){
            for(int j = 0; j < world.readSize(); j++){
                if(instanceof<Heracleum_sosnowskyi>(world.readOrganism(Point(i,j)))){
                    a = this->position.x - i;
                    b = this->position.y - j;
                    distance = sqrt(pow(a,2)+pow(b,2));
                    queue.push_back(std::pair<Point,float>(Point(i,j), distance));
                }
            }
        }

        if(queue.size() != 0){
            sort(queue.begin(), queue.end(), sortbysec);

            this->previous_position = Point(position.x, position.y);

            Point destination = queue[0].first;

            if(destination.x > position.x){
                position.x +=1;
            }
            else if(destination.x < position.x){
                position.x -=1;
            }
            else if(destination.y > position.y){
                position.y +=1;
            }
            else if(destination.y < position.y){
                position.y -=1;
            }

            int world_size = world.readSize();

            position.x %= world_size;
            position.y %= world_size;

            if(position.x < 0){
                position.x += world_size;
            }
            if(position.y < 0){
                position.y += world_size;
            }

            char message[256];
            sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
            world.takeEvent(message);

            world.updatePosition(this);
        }
        else{
            Animal::action(world);
        }
    }
    catch(mException mexception){

        std::cout<<"cybersheep_action_ "<<mexception.text;
    }

}

Cybersheep* Cybersheep::createChild(const Point& position) const
{
    return new Cybersheep(position.x, position.y);
}