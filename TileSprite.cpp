#include "TileSprite.hpp"

/********** IMAGES  ************/

Images::Images(){

}

Images::Images(bool){
    skyimg.LoadFromFile("resources/sky.png");
    grassimg.LoadFromFile("resources/GrassTile.png");
    earthimg.LoadFromFile("resources/EarthTile.png");
    appleimg.LoadFromFile("resources/Apple.png");
    rocketlauncherimg.LoadFromFile("resources/Rocketlauncher.png");
    rocketimg.LoadFromFile("resources/Rocket.png");
}

Images I(true);

/*******************************/



/*******    APPEARANCES    *********/

BlockAppearances::BlockAppearances(){

}

BlockAppearances::BlockAppearances(bool){
    push_back(I.skyimg);
    push_back(I.earthimg);
    push_back(I.grassimg);
}

BlockAppearances::~BlockAppearances(){

}

sf::Sprite& BlockAppearances::operator[](unsigned int ID){
    return a[ID];
}

void BlockAppearances::push_back(const sf::Image& i){
    a.push_back(sf::Sprite(i));
}

BlockAppearances BA(1);



/*******************************/


/*******    TILESPRITE   ********/

TileSprite::TileSprite(){
    appearance = &BA[0];
    xPosition = 0;
    yPosition = 0;
}

TileSprite::TileSprite(unsigned int ID){
    appearance = &BA[ID];
    xPosition = 0;
    yPosition = 0;
}

TileSprite::~TileSprite(){
    appearance = NULL;
}

void TileSprite::SetAppearance(sf::Sprite& a){
    appearance = &a;
}

const sf::Sprite* TileSprite::GetAppearance() const{
    return appearance;
}

void TileSprite::Draw(sf::RenderWindow& W){
    appearance->SetPosition(xPosition, yPosition);
    W.Draw(*appearance);
}

/****************************/
