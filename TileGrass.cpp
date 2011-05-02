#include "TileGrass.hpp"

TileGrass::TileGrass(){
    id = GRASS;
    appearance = &BA[id];
    collide = true;
}

TileGrass::~TileGrass(){

}

TileAABB* TileGrass::Clone(){
    return new TileGrass(*this);
}
