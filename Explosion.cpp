#include "Explosion.hpp"

Explosion::Explosion(World& w, unsigned int colX, unsigned int colY, unsigned int radius){
    Radius = radius;
    Explode(w, colX, colY);
    this->~Explosion();
}

Explosion::~Explosion(){

}

void Explosion::Explode(World& w, int colX, int colY){
    for(int rad=1; rad<Radius; rad++){
        if(colX + rad < w.map->GetNbrColumns() - 2)
            if(w.map->TileExists(colX + rad, colY))
                w.map->ReplaceElementWith(colX + rad, colY, SKY);
        if(colX - rad > 2)
            if(w.map->TileExists(colX - rad, colY))
                w.map->ReplaceElementWith(colX - rad, colY, SKY);
        if(colY + rad < w.map->GetNbrTilesPerColumn() - 2)
            if(w.map->TileExists(colX, colY + rad))
                w.map->ReplaceElementWith(colX, colY + rad, SKY);
        if(colY - rad > 2)
            if(w.map->TileExists(colX, colY - rad))
                w.map->ReplaceElementWith(colX, colY - rad, SKY);
    }

    int maxX = Radius - 1;
    int maxY = Radius - 1;
    int minX = -maxX;
    int minY = -maxY;


    for(int i=0; i<maxX; ++i){
        if(colX + i <= w.map->GetNbrColumns() - 1)
            if(w.map->TileExists(colX + i, colY))
                w.map->ReplaceElementWith(colX + i, colY, SKY);
    }

    for(int i=0; i>minX; --i){
        if(colX + i >= 0)
            if(w.map->TileExists(colX + i, colY))
                w.map->ReplaceElementWith(colX + i, colY, SKY);
    }


    for(int i=0; i<maxX; ++i){
        for(int j=maxY - i; j>0; --j){
            if(w.map->TileExists(colX + i, colY + j))
                w.map->ReplaceElementWith(colX + i, colY + j, SKY);
            if(w.map->TileExists(colX + i, colY - j))
                w.map->ReplaceElementWith(colX + i, colY - j, SKY);

        }
    }

    for(int i=0; i>minX; --i){
        for(int j=minY - i; j<0; ++j){
            if(w.map->TileExists(colX + i, colY + j))
                w.map->ReplaceElementWith(colX + i, colY + j, SKY);
            if(w.map->TileExists(colX + i, colX + j))
                w.map->ReplaceElementWith(colX + i, colY - j, SKY);
        }
    }

    if(w.map->TileExists(colX, colY))
        w.map->ReplaceElementWith(colX, colY, SKY);

    w.map->ComputeCollisions();
}

