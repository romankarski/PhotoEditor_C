#include "Human.hpp"
#include "World.hpp"
#include "mException.hpp"


Human::Human(int x, int y) : Animal(x, y)
{
    left_turns_break = 0;
    left_turns_period = 0;
    strength = 5;
    initiative = 4;
    sign = 'H';
    species = Species::HUMAN;
    speciesText = "Human";
}

void Human::action(World& world)
{
    /*
    lewo 68
    prawo 67
    gora 65
    dol 66
    spacja 32
    */
    try{


            if(left_turns_period == 0){
                if(left_turns_break > 0) 
                    left_turns_break--;
            }
            if(left_turns_period > 0) left_turns_period--;
            

            previous_position = position;

            char message[256];
            char input_usr;

            input_usr = world.getInput();

            if(input_usr == 65) position.x -= 1;
            if(input_usr == 66) position.x += 1;
            if(input_usr == 68) position.y -= 1;
            if(input_usr == 67) position.y += 1;
            if(input_usr == 32) {
                if(left_turns_break == 0){ left_turns_period = 5; left_turns_break = 5;
                    sprintf(message, "%s is using immortality",speciesText.c_str());
                    world.takeEvent(message);
                }
                else {
                    sprintf(message, "%s cannot use immortality",speciesText.c_str());
                    world.takeEvent(message);
                }
            }

            int world_size = world.readSize();
            if(previous_position != position){

                position.x %= world_size;
                position.y %= world_size;

                if(position.x < 0) position.x += world_size;
                if(position.y < 0) position.y += world_size;


                sprintf(message, "%s is moving from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
                world.takeEvent(message);
                world.updatePosition(this);
            }   
            std::cout<<"break : "<<left_turns_break<<" | period : "<<left_turns_period<<"\n";
            sprintf(message, "break : %d  |  period : %d ", left_turns_break, left_turns_period);
            world.takeEvent(message);
    }
    catch(mException mexception){

        std::cout<<"human_action_ "<<mexception.text;
    }

}

void Human::collision(World& world, Organism* other_organism, const bool reproduction_possible)
{
    if(alive && other_organism && other_organism->isAlive()){
        Animal::collision(world, other_organism, reproduction_possible);
    }
}

void Human::death(World& world)
{
    if(left_turns_period > 0){
        try{
            Point pos;
            pos = position;

            position = takeNeighbouringPosition(world);

            char message[256];
            sprintf(message, "%s was immortal, survived and moved from (%d,%d) to (%d,%d)",speciesText.c_str(),previous_position.x,previous_position.y,position.x,position.y);
            world.takeEvent(message);

            world.updatePosition(this);
            previous_position = pos;
        }
        catch(mException mexception){
            mexception.text = "human_action_immortality_ ";
            std::cout<<mexception.text;
        }
    }   
    else{
        alive = false;
    }
}


Human* Human::createChild(const Point& position) const
{
    return new Human(position.x, position.y);
}