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
        float xVel;
        float yVel;
        float length;
        xVel = targetX - w.player->CenterX();
        yVel = targetY - w.player->CenterY();
        length = sqrt(xVel * xVel + yVel * yVel);

        xVel /= length;
        yVel /= length;


        if(xVel == 0)
            xVel = 1;
        if(yVel == 0)
            yVel = 1;

        xVel *= 1.7f;
        yVel *= 1.7f;

        w.AddMissile(Ammo, xVel, yVel);
        ready = false;
    }
}



