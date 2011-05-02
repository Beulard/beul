#include "Missile.hpp"


MissileAppearances::MissileAppearances(bool){
    push_back(I.rocketimg);
}

MissileAppearances MA(true);




MissileList missileList;


void MissileList::RegisterMissile(Missile* m){
    missiles.push_back(m);
}

Missile* MissileList::operator[](unsigned int index){
    try{
        if(index > missiles.size() - 1)
            throw 0;
        else
            return missiles[index];
    }
    catch(int){
        std::cout << "Cant access missiles[" << index << "], returning missiles[0]." << std::endl;
        return missiles[0];
    }
}

Missile::Missile(){

}

Missile::~Missile(){

}

void Missile::onCollision(World& w, unsigned int thisID, unsigned int sourceX, unsigned int sourceY){

}
