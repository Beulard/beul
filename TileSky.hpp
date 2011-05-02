#ifndef BEUL_TILESKY
#define BEUL_TILESKY

#include "TileAABB.hpp"


class TileSky : public TileAABB{
    public:
        TileSky();
        ~TileSky();

        virtual TileAABB* Clone();

    private:
};

#endif // BEUL_TILESKY
