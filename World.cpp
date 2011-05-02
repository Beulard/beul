#include "World.hpp"

World::World(Map& m, Player& p){
    //  Tiles Initialization  //
    tileList.RegisterTile(new TileSky());
    tileList.RegisterTile(new TileEarth());
    tileList.RegisterTile(new TileGrass());


    //  Items Initialization  //
    itemList.RegisterItem(new Apple());
    itemList.RegisterItem(new RocketLauncher());

    //  Missiles Initialization  //
    missileList.RegisterMissile(new Rocket());


    player = &p;
    map = &m;

    //  Map Generation  //
    //map->GenerateRandomElements();
}

World::~World(){

}

void World::AddMissile(unsigned int ID, int xVel, int yVel){
    missiles.push_back(missileList[ID]->Clone());
    missiles.back()->AABB::SetPosition(player->CenterX(), player->CenterY());
    missiles.back()->SetXVelocity(xVel);
    missiles.back()->SetYVelocity(yVel);
}

void World::DeleteMissile(unsigned int index){
    delete missiles[index];
    missiles.erase(missiles.begin() + index);
}

void World::Draw(sf::RenderWindow& W){
    for(unsigned int i=0; i<missiles.size(); ++i){
        missiles[i]->Move();
        missiles[i]->Draw(W);
        //std::cout << missiles.size() << std::endl;
        if(missiles[i]->Right() < W.GetView().GetRect().Left || missiles[i]->Left() > W.GetView().GetRect().Right || missiles[i]->Down() < 0 || missiles[i]->Up() > map->GetNbrTilesPerColumn() * TILES_SIZE)
            DeleteMissile(i);
    }
}
