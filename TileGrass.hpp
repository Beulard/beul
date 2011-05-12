#ifndef BEUL_TILEGRASS
#define BEUL_TILEGRASS

#include "TileAABB.hpp"


class TileGrass : public TileAABB{
    public:
        TileGrass();
        ~TileGrass();

        virtual TileAABB* Clone();

        virtual const bool Collides()   const;

        virtual void onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source);

    private:
};

#endif // BEUL_TILEGRASS
