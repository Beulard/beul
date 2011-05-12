#include "Rocket.hpp"

Rocket::Rocket(){
    id = ROCKET;
    appearance = &MA[id];
    explosionRadius = 4;
    width = 32;
    height = 19;
}

Rocket::Rocket(unsigned int radius){
    id = ROCKET;
    appearance = &MA[id];
    explosionRadius = radius;
}

Rocket::~Rocket(){

}

Missile* Rocket::Clone(){
    return new Rocket(*this);
}

void Rocket::onCollision(World& w, unsigned int colX, unsigned int colY, unsigned int thisIndex){
    w.map->GetElements()[colX][colY]->onCollisionWithRocket(w, colX, colY, thisIndex);
    w.map->NeedsRePlacing(true);
}

const unsigned int Rocket::GetExplosionRadius() const{
    return explosionRadius;
}

