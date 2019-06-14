#ifndef __Organism__
#define __Organism__

#include <iostream>

class World;

class Point
{
    public:
        Point() : Point(0, 0) {}
        Point(int _x, int _y) : x(_x), y(_y) {}

        int x;
        int y;

        bool operator != (const Point& other)
        {
            return x != other.x || y != other.y;
        }

        bool operator == (const Point& other)
        {
            return x == other.x && y == other.y;
        }
};

enum Species
{
    // Fauna
    WOLF,
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    CYBERSHEEP,
    HUMAN,
    // Flora
    GRASS,
    SOWTHISTLE,
    GUARANA,
    DEADLY_NIGHTSHADE,
    HERACLEUM_SOSNOWSKYI

};

class Organism
{
    public:
        Organism(int x, int y);
        virtual ~Organism() = default;

        virtual void action(World& world) = 0;
        virtual void collision(World& world, Organism* otherOrganism, const bool reproduction_possible = true) = 0;
        virtual void draw() const = 0;
        virtual void death(World& world) { alive = false; }
        virtual Organism* createChild(const Point& position) const = 0;

        Point readPosition() const { return position; }
        Point readPreviousPosition() const { return previous_position; }
        Species getSpecies() const { return species; }
        char getSign() const { return sign; }
        int getStrength() const { return strength; }
        int getAge() const { return age; }
        bool isAlive() const { return alive; }
        bool isFlora() const { return species >= GRASS; }
        void increaseStrength(const int additional_strength) { strength += additional_strength; }
        std::string readSpeciesText() const { return speciesText; }
    
        bool operator > (const Organism& other);

    protected:
        int strength;
        int initiative;
        int age;
        bool alive;
        char sign;
        Species species;
        std::string speciesText;

        Point position;
        Point previous_position;

        Point takeNeighbouringPosition(World& world, const bool is_taken_position = true, const Point* to_avoid = nullptr) const;
};

#endif // defin __Organism__