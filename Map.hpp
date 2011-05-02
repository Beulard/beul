#ifndef BEUL_MAP
#define BEUL_MAP
#include "Grid.hpp"
#include "MapManager.hpp"
#include "Player.hpp"
#include "World.hpp"
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>
#include "TileAABB.hpp"
#include "RocketLauncher.hpp"
#include "Apple.hpp"

#define TILES_SIZE 32

std::string IntToString(const int i);

class Map{
    public:
        Map();
        Map(const Grid& g);
        Map(unsigned int width, unsigned int height);
        Map(const Grid& g, MapManager& mm);
        ~Map();

        void GetElementsFromFile(MapManager& mm);   //TODO

        void GenerateRandomElements();
        void Draw(sf::RenderWindow& W);

        void RePlaceElements(sf::RenderWindow& W);

        void AddElement(unsigned int ID);
        void DeleteElement(unsigned int x, unsigned int y);
        void ReplaceElementWith(unsigned int x, unsigned int y, unsigned int ID);
        void AddItem(unsigned int ID, int xPos, int yPos);
        void DeleteItem(unsigned int index);

        bool TileExists(int x, int y)   const;

        const TileAABB* GetTile(int x, int y)   const;
        const TileAABB* GetAboveTile(int x, int y)    const;
        const TileAABB* GetBelowTile(int x, int y)    const;
        const TileAABB* GetRightTile(int x, int y)    const;
        const TileAABB* GetLeftTile(int x, int y)    const;

        const unsigned int GetNbrColumns()  const;
        const unsigned int GetNbrTilesPerColumn()   const;

        void ComputeCollisions();
        //const std::vector<TileAABB**> GetCollisions();

        //void FastGetCollisions(const Player& p, std::vector<unsigned int>& iCollisions, std::vector<unsigned int>& jCollisions);

        const std::vector< std::vector< TileAABB* > >& GetElements()   const;
        const std::vector< Item* >& GetItems()  const;

        const unsigned int GetNbrElements()   const;


    private:


        TileAABB* privGetTile(int x, int y);
        TileAABB* privGetAboveTile(int x, int y);
        TileAABB* privGetBelowTile(int x, int y);
        TileAABB* privGetRightTile(int x, int y);
        TileAABB* privGetLeftTile(int x, int y);




        std::vector< std::vector< TileAABB* > > elements;
        std::vector< Item* > items;
        //std::vector<TileAABB**> collisions;
        unsigned int nbrColumns;
        unsigned int nbrTilesPerColumn;
        bool needRePlacing;
};

#endif // BEUL_MAP
