#include "Frame.hpp"

Frame::Frame(){
    sprite = NULL;
    time = 1.f;
}

Frame::Frame(sf::Sprite& s, float fTime){
    sprite = &s;
    time = fTime;
}

Frame::~Frame(){

}

void Frame::SetFrameTime(float fTime){
    time = fTime;
}

const float Frame::GetFrameTime()   const{
    return time;
}

void Frame::Draw(sf::RenderWindow& W){
    if(sprite)
        W.Draw(*sprite);
}

void Frame::SetPosition(int x, int y){
    if(sprite)
        sprite->SetPosition(x, y);
}
