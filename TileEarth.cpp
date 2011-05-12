#include "TileEarth.hpp"
#include "Explosion.hpp"

TileEarth::TileEarth(){
    id = EARTH;
    appearance = &BA[id];
    eReaction = EXPLOSION;
}

TileEarth::~TileEarth(){

}

TileAABB* TileEarth::Clone(){
    return new TileEarth(*this);
}

const bool TileEarth::Collides()    const{
    return true;
}

void TileEarth::onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source){
    ExplodeParams* ep = new ExplodeParams();
    ep->w = &w;
    ep->colX = indexX;
    ep->colY = indexY;
    ep->index = source;
    ep->rad = dynamic_cast<Rocket*>(w.missiles[source])->GetExplosionRadius();
    ER[EXPLOSION](ep);
}
