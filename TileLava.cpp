#include "TileLava.hpp"
#include "World.hpp"

TileLava::TileLava(){
    id = LAVA;
    aid = ALAVA;

    anim = new Animation(animationList[aid]);
    anim->SetPosition(left, up);
    appearance = NULL;
    width = 12;
    height = 12;
    eReaction = DELETE_MISSILE;
}

TileLava::~TileLava(){
    anim = NULL;
}


TileAABB* TileLava::Clone(){
    return new TileLava(*this);
}

void TileLava::Draw(sf::RenderWindow& W){
    anim->SetPosition(left - 10, up - 10);
    anim->Animate(W.GetFrameTime());
    anim->Draw(W);
}

void TileLava::onCollision(World& w){
    if(w.player->Collision(*this)){
        w.player->Die();
    }
}

void TileLava::onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source){
    DeleteMissileParams* dmp = new DeleteMissileParams();
    dmp->index = source;
    dmp->w = &w;
    ER[DELETE_MISSILE](dmp);
}

const bool TileLava::Collides() const{
    return false;
}

void TileLava::SetPosition(float x, float y){
    AABB::SetPosition(x + 10, y + 10);
}
