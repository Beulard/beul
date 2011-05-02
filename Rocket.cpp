#include "Rocket.hpp"

Rocket::Rocket(){
    id = ROCKET;
    appearance = &MA[id];
    explosionRadius = 4;
    width = 29;
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

void Rocket::onCollision(World& w, unsigned int thisIndex, unsigned int colX, unsigned int colY){
    Explosion e(w, colX, colY, explosionRadius);
    //std::cout << "cheval" << std::endl;
    w.DeleteMissile(thisIndex);
}
