#ifndef BEUL_TILEEARTH
#define BEUL_TILEEARTH

#include "TileAABB.hpp"


class TileEarth : public TileAABB{
    public:
        TileEarth();
        ~TileEarth();

        virtual TileAABB* Clone();

    private:
};

#endif // BEUL_TILEEARTH
