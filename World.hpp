#ifndef BEUL_WORLD
#define BEUL_WORLD

class Map;
class Player;

#include "TileSky.hpp"
#include "TileEarth.hpp"
#include "TileGrass.hpp"
#include "TileLava.hpp"
#include "Apple.hpp"
#include "RocketLauncher.hpp"
#include "Rocket.hpp"
#include "RocketRepeater.hpp"

class World
{
    public:
        World(Map& m, Player& p);
        ~World();

        void AddMissile(unsigned int ID, float xAcc, float yAcc);
        void DeleteMissile(unsigned int index);

        void Draw(sf::RenderWindow& W);

        Map* map;
        Player* player;
        std::vector<Missile*> missiles;
        std::vector<unsigned int> del;
};

#endif // BEUL_WORLD
