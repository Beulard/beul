#ifndef BEUL_TILEAABB
#define BEUL_TILEAABB

#include "TileSprite.hpp"
#include "AABB.hpp"

class World;
class TileAABB;
class Params;

typedef void (*ptr_void)(Params*);

enum ExplosionReaction{
    DO_NOTHING,
    EXPLOSION,
    DELETE_MISSILE
};

class TileList{
    public:
        void RegisterTile(TileAABB* t);
        TileAABB* operator[](unsigned int index);
        const unsigned int size()   const;
    private:
        std::vector<TileAABB*> tiles;
};

extern TileList tileList;



class CExplosionReaction{
    public:
        CExplosionReaction();
        CExplosionReaction(bool);
        ptr_void operator[](unsigned int index);
    private:
        std::vector<ptr_void> reactions;

};

extern CExplosionReaction ER;


class TileAABB : public TileSprite, public AABB{
    public:
        TileAABB();
        ~TileAABB() = 0;

        virtual TileAABB* Clone() = 0;

        virtual void Draw(sf::RenderWindow& W);
        void Move();

        virtual void onCollision(World& w);

        /* param : w = the world;
            param : indexX = X index of this TileAABB in the map;
            param : indexY = Y index of this TileAABB in the map;
            param : source = index of the missile colliding; */
        virtual void onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source);

        void operator=(unsigned int ID);
        const bool operator==(unsigned int ID)    const;

    protected:
        ExplosionReaction eReaction;
};

#endif // BEUL_TILEAABB
