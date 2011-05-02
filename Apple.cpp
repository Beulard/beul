#include "Apple.hpp"

Apple::Apple(){
    id = APPLE;
    appearance = &IA[id];
}

Apple::~Apple(){

}

Item* Apple::Clone(){
    return new Apple(*this);
}

void Apple::onGet(World& w){

}

void Apple::onUse(World& w, int targetX, int targetY){

}

