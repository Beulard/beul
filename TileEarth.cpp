#include "TileEarth.hpp"

TileEarth::TileEarth(){
    id = EARTH;
    appearance = &BA[id];
    collide = true;
}

TileEarth::~TileEarth(){

}

TileAABB* TileEarth::Clone(){
    return new TileEarth(*this);
}
