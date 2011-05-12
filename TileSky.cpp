#include "TileSky.hpp"
#include "Explosion.hpp"

TileSky::TileSky(){
    id = SKY;
    appearance = &BA[id];
    eReaction = DO_NOTHING;
}

TileSky::~TileSky(){

}

TileAABB* TileSky::Clone(){
    return new TileSky(*this);
}

const bool TileSky::Collides()  const{
    return false;
}

void TileSky::onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source){
    DoNothingParams* dnp = new DoNothingParams();
    ER[DO_NOTHING](dnp);
}
