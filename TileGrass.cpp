#include "TileGrass.hpp"
#include "Explosion.hpp"

TileGrass::TileGrass(){
    id = GRASS;
    appearance = &BA[id];
    eReaction = EXPLOSION;
}

TileGrass::~TileGrass(){

}

TileAABB* TileGrass::Clone(){
    return new TileGrass(*this);
}

const bool TileGrass::Collides()    const{
    return true;
}

void TileGrass::onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source){
    ExplodeParams* ep = new ExplodeParams();
    ep->w = &w;
    ep->colX = indexX;
    ep->colY = indexY;
    ep->index = source;
    ep->rad = dynamic_cast<Rocket*>(w.missiles[source])->GetExplosionRadius();
    ER[EXPLOSION](ep);
}
