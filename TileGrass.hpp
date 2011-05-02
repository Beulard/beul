#ifndef BEUL_TILEGRASS
#define BEUL_TILEGRASS

#include "TileAABB.hpp"


class TileGrass : public TileAABB{
    public:
        TileGrass();
        ~TileGrass();

        virtual TileAABB* Clone();

    private:
};

#endif // BEUL_TILEGRASS
