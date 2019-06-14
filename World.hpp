#ifndef __World__
#define __World__

#include "Wolf.hpp"
#include "Sheep.hpp"
#include "Fox.hpp"
#include "Turtle.hpp"
#include "Antelope.hpp"
#include "Human.hpp"
#include "Grass.hpp"
#include "Sowthistle.hpp"
#include "Guarana.hpp"
#include "Deadly_nightshade.hpp"
#include "Heracleum_sosnowskyi.hpp"
#include "Cybersheep.hpp"

#include <vector>
#include <algorithm>

class World{
    public:
        World(const int world_size = 15, const bool is_infinite = false);

        void makeTurn();
        void drawWorld();
        void addOrganism(int x, int y, int choice);
        void putOrganism(Organism* organism);
        void deleteOrganism(const Point& position);
        void updatePosition(Organism* organism);
        void takeEvent(const std::string& message);
        void setInput(char input) { this->input = input; }
        char getInput() { return input; }

        int readSize() const { return organisms.size(); }
        bool isInfinite() const { return is_infinite; }
        Organism* readOrganism(const Point& position) const { return organisms[position.x][position.y]; }
    
    private:
        const int min_size;
        bool is_infinite;
        int current_turn;
        std::vector<std::vector<Organism*>> organisms;
        std::vector<std::string> events;
        char input;

        template <class TOrganism>
        void putOrganism(int x, int y);

        void sortOrganisms(std::vector<Organism*>& sorted_organisms) const;
        void deleteDeadOrganisms();
};

#endif // define __World__
