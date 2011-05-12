#ifndef BEUL_TILESKY
#define BEUL_TILESKY

#include "TileAABB.hpp"


class TileSky : public TileAABB{
    public:
        TileSky();
        ~TileSky();

        virtual TileAABB* Clone();
        virtual const bool Collides() const;

        virtual void onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source);

    private:
};

#endif // BEUL_TILESKY
