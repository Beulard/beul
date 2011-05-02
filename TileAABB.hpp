#ifndef BEUL_TILEAABB
#define BEUL_TILEAABB

#include "TileSprite.hpp"
#include "AABB.hpp"

class TileAABB;

class TileList{
    public:
        void RegisterTile(TileAABB* t);
        TileAABB* operator[](unsigned int index);
        std::vector<TileAABB*> tiles;
};

extern TileList tileList;

class TileAABB : public TileSprite, public AABB{
    public:
        TileAABB();
        //TileAABB(unsigned int ID);
        ~TileAABB() = 0;

        virtual TileAABB* Clone() = 0;

        void Draw(sf::RenderWindow& W);
        void Move();

        const bool Collides()   const;

        void operator=(unsigned int ID);
        const bool operator==(unsigned int ID)    const;

    protected:

};

#endif // BEUL_TILEAABB
