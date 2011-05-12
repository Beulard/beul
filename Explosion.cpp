#include "Explosion.hpp"
#include "World.hpp"

DoNothingParams* DNP = new DoNothingParams();

ExplodeParams* EP = new ExplodeParams();

DeleteMissileParams* DMP = new DeleteMissileParams();


ExplosionReactionParams::ExplosionReactionParams(){

}

ExplosionReactionParams::ExplosionReactionParams(bool){
    params.push_back(DNP);
    params.push_back(EP);
    params.push_back(DMP);
}

Params* ExplosionReactionParams::operator[](unsigned int index){
    try{
        if(index > params.size() - 1)
            throw 0;
        else
            return params[index];
    }
    catch(int){
        std::cerr << "Can't access ExplosionReactionParams[" << index << "], returning ExplosionReactionParams[0]." << std::endl;
        return params[0];
    }
}

ExplosionReactionParams ERP(1);


void DoNothing(Params* params){

}

void Explode(Params* params){
    ExplodeParams* ep = dynamic_cast<ExplodeParams*>(params);
    Explosion e(*ep->w, ep->colX, ep->colY, ep->rad);
    ep->w->DeleteMissile(ep->index);
}

void DeleteMissile(Params* params){
    DeleteMissileParams* dmp = dynamic_cast<DeleteMissileParams*>(params);
    dmp->w->DeleteMissile(dmp->index);
}

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
            if(w.map->TileExists(colX + i, colY - j))
                w.map->ReplaceElementWith(colX + i, colY - j, SKY);
        }
    }

    if(w.map->TileExists(colX, colY))
        w.map->ReplaceElementWith(colX, colY, SKY);

    //w.map->ComputeCollisions();
}

