#include "RocketRepeater.hpp"
#include "World.hpp"

RocketRepeater::RocketRepeater(){
    id = ROCKETREPEATER;
    appearance = &IA[id];
    Ammo = ROCKET;
    reloadTime = 0.2f;
    ready = true;
}

RocketRepeater::~RocketRepeater(){

}

Item* RocketRepeater::Clone(){
    return new RocketRepeater(*this);
}

void RocketRepeater::onGet(World& w){
    w.player->SetWeapon(ROCKETREPEATER);
}
