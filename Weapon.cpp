#include "Weapon.hpp"

Weapon::Weapon(){
    id = static_cast<ItemID>(0);
    currentTime = 0.f;
    reloadTime = 1.f;
    ready = true;
}

Weapon::~Weapon(){

}

void Weapon::Reload(float frameTime){
    if(!ready){
        currentTime += frameTime;
        if(currentTime >= reloadTime){
            ready = true;
            currentTime = 0.f;
        }
    }
}
