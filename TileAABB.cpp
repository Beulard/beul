#include "TileAABB.hpp"

TileList tileList;

void TileList::RegisterTile(TileAABB* t){
    tiles.push_back(t);
}

TileAABB* TileList::operator[](unsigned int index){
    try{
        if(index > tiles.size() - 1)
            throw 0;
        else
            return tiles[index];
    }
    catch(int){
        std::cout << "Cant access tiles[" << index << "], returning tiles[0]." << std::endl;
        return tiles[0];
    }
}

TileAABB::TileAABB(){
    id = SKY;
    appearance = &BA[SKY];
    collide = true;
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
    Tile::SetPosition(left, up);
    appearance->SetPosition(left, up);
    W.Draw(*appearance);
}

void TileAABB::Move(){
    AABB::Move();
    appearance->SetPosition(left, up);
}

const bool TileAABB::Collides() const{
    return collide;
}

void TileAABB::operator=(unsigned int ID){
    /*appearance = &BA[ID];
    id = static_cast<TileID>(ID);*/
    *this = *tileList[ID]->Clone();
}

const bool TileAABB::operator==(unsigned int ID)    const{
    if(id == ID)
        return true;
    return false;
}
