#include "Lava.hpp"

Lava::Lava(){

}

Lava::~Lava(){

}

TileAABB* Lava::Clone(){
    return new Lava(
