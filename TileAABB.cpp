#include "TileAABB.hpp"
#include "Explosion.hpp"

TileList tileList;

void TileList::RegisterTile(TileAABB* t){
    tiles.push_back(t);
}

TileAABB* TileList::operator[](unsigned int index){
    try{
        if(index > tiles.size() - 1)
            throw 0;
        else
            return tiles[index]->Clone();
    }
    catch(int){
        std::cerr << "Cant access TileList[" << index << "], returning TileList[0]." << std::endl;
        return tiles[0]->Clone();
    }
}

const unsigned int TileList::size() const{
    return tiles.size();
}


CExplosionReaction::CExplosionReaction(){

}

CExplosionReaction::CExplosionReaction(bool){
    ptr_void ptr_DoNothing = &DoNothing;
    ptr_void ptr_Explode = &Explode;
    ptr_void ptr_DeleteMissile = &DeleteMissile;
    reactions.push_back(ptr_DoNothing);
    reactions.push_back(ptr_Explode);
    reactions.push_back(ptr_DeleteMissile);
}

ptr_void CExplosionReaction::operator[](unsigned int index){
    try{
        if(index > reactions.size() - 1)
            throw 0;
        else
            return reactions[index];
    }
    catch(int){
        std::cerr << "Can't access CExplosionReaction[" << index << "], returning CExplosionReaction[0]." << std::endl;
    }
}

CExplosionReaction ER(1);

TileAABB::TileAABB(){
    id = SKY;
    appearance = &BA[SKY];
    eReaction = DO_NOTHING;
}

/*TileAABB::TileAABB(unsigned int ID){
    appearance = &BA[ID];
    id = static_cast<TileID>(ID);
    xPosition = 0;
    yPosition = 0;
}*/

TileAABB::~TileAABB(){

}

void TileAABB::Draw(sf::RenderWindow& W){
    SetPos(left, up);
    appearance->SetPosition(left, up);
    W.Draw(*appearance);
}

void TileAABB::Move(){
    AABB::Move();
    appearance->SetPosition(left, up);
}

void TileAABB::operator=(unsigned int ID){
    /*appearance = &BA[ID];
    id = static_cast<TileID>(ID);*/
    *this = *tileList[ID];
}

const bool TileAABB::operator==(unsigned int ID)    const{
    if(id == ID)
        return true;
    return false;
}

void TileAABB::onCollision(World& w){

}

void TileAABB::onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source){
    DoNothingParams* dnp = new DoNothingParams();
    ER[eReaction](dnp);
}
