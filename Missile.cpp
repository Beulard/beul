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
            return missiles[index]->Clone();
    }
    catch(int){
        std::cerr << "Cant access MissileList[" << index << "], returning MissileList[0]." << std::endl;
        return missiles[0]->Clone();
    }
}

const unsigned int MissileList::size()  const{
    return missiles.size();
}

Missile::Missile(){

}

Missile::~Missile(){

}

void Missile::onCollision(World& w, unsigned int colX, unsigned int colY, unsigned int thisIndex){}
