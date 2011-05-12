#ifndef BEUL_TILEEARTH
#define BEUL_TILEEARTH

#include "TileAABB.hpp"


class TileEarth : public TileAABB{
    public:
        TileEarth();
        ~TileEarth();

        virtual TileAABB* Clone();

        virtual const bool Collides()   const;

        virtual void onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source);


    private:
};

#endif // BEUL_TILEEARTH
