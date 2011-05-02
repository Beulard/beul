#include "RocketLauncher.hpp"

RocketLauncher::RocketLauncher(){
    id = ROCKETLAUNCHER;
    appearance = &IA[id];
    Ammo = ROCKET;
    reloadTime = 0.7f;
    ready = true;
}

RocketLauncher::~RocketLauncher(){

}

Item* RocketLauncher::Clone(){
    return new RocketLauncher(*this);
}

void RocketLauncher::onGet(World& w){
    w.player->SetWeapon(ROCKETLAUNCHER);
}

void RocketLauncher::onUse(World& w, int targetX, int targetY){
    if(ready){
        std::cout << "FIRE" << std::endl;
        float xVel;
        float yVel;
        xVel = (targetX - w.player->CenterX()) / 10000.f * 775/* / 1000.f * 75.f*/;
        yVel = (targetY - w.player->CenterY()) / 10000.f * 775/* / 1000.f * 75.f*/;
        std::cout << yVel << std::endl;
        if(xVel == 0)
            xVel = 1;
        if(yVel == 0)
            yVel = 1;
        //std::cout << targetX << '\n' << targetY  << std::endl;
        w.AddMissile(Ammo, xVel, yVel);
        ready = false;
    }
}



