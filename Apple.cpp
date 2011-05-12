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
    if(w.player->GetLives() < 3)
        w.player->AddLife();
}

void Apple::onUse(World& w, int targetX, int targetY){

}

