#include "TileSky.hpp"

TileSky::TileSky(){
    collide = false;
    id = SKY;
    appearance = &BA[id];
}

TileSky::~TileSky(){

}

TileAABB* TileSky::Clone(){
    return new TileSky(*this);
}
