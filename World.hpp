#ifndef BEUL_WORLD
#define BEUL_WORLD

class Map;
class Player;

#include "TileSky.hpp"
#include "TileEarth.hpp"
#include "TileGrass.hpp"
#include "Apple.hpp"
#include "RocketLauncher.hpp"
#include "Rocket.hpp"

class World
{
    public:
        World(Map& m, Player& p);
        ~World();

        void AddMissile(unsigned int ID, int xVel, int yVel);
        void DeleteMissile(unsigned int index);

        void Draw(sf::RenderWindow& W);

        Map* map;
        Player* player;
        std::vector<Missile*> missiles;
};

#endif // BEUL_WORLD
