#include "Tile.hpp"

Tile::Tile(){
    xPosition = 0;
    yPosition = 0;
}

Tile::~Tile(){

}

void Tile::Draw(sf::RenderWindow& W){

}

void Tile::SetPosition(int x, int y){
    xPosition = x;
    yPosition = y;
}

const int Tile::GetXPosition()  const{
    return xPosition;
}

const int Tile::GetYPosition()  const{
    return yPosition;
}

const unsigned int Tile::GetID()    const{
    return id;
}

void Tile::operator=(unsigned int ID){
    id = static_cast<TileID>(ID);
}
