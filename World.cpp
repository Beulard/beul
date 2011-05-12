#include "World.hpp"

World::World(Map& m, Player& p){
    //  Tiles Initialization  //
    tileList.RegisterTile(new TileSky());
    tileList.RegisterTile(new TileEarth());
    tileList.RegisterTile(new TileGrass());
    tileList.RegisterTile(new TileLava());


    //  Items Initialization  //
    itemList.RegisterItem(new Apple());
    itemList.RegisterItem(new RocketLauncher());
    itemList.RegisterItem(new RocketRepeater());

    //  Missiles Initialization  //
    missileList.RegisterMissile(new Rocket());


    player = &p;
    map = &m;

    //  Map Generation  //
    //map->GenerateRandomElements();
}

World::~World(){
    for(unsigned int i=0; i<missiles.size(); ++i)
        delete missiles[i];
}

void World::AddMissile(unsigned int ID, float xAcc, float yAcc){
    missiles.push_back(missileList[ID]);
    missiles.back()->AABB::SetPosition(player->CenterX() - missiles.back()->Width() / 2, player->CenterY() - missiles.back()->Width() / 2);
    missiles.back()->SetXVelocity(xAcc);
    missiles.back()->SetYVelocity(yAcc);
}

void World::DeleteMissile(unsigned int index){
    if(missiles.size() > 1){
        delete missiles[index];
        if(index != missiles.size() - 1){
            missiles[index] = missiles.back()->Clone();
            delete missiles[missiles.size() - 1];
        }
        missiles.pop_back();
    }
    else if(missiles.size() == 1){
        delete missiles[index];
        missiles.clear();
    }
}

void World::Draw(sf::RenderWindow& W){
    for(unsigned int i=0; i<missiles.size(); ++i){
        missiles[i]->Accelerate();
        missiles[i]->SetPosition(missiles[i]->Left() + missiles[i]->XVelocity(), missiles[i]->Up() + missiles[i]->YVelocity());
        missiles[i]->Draw(W);

        if(missiles[i]->Right() < 0 || missiles[i]->Left() > map->GetNbrColumns() * TILES_SIZE || missiles[i]->Down() < 0 || missiles[i]->Up() > map->GetNbrTilesPerColumn() * TILES_SIZE)
            DeleteMissile(i);
    }

}
