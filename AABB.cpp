#include "AABB.hpp"

AABB::AABB(){
    left = 0;
    up = 0;
    width = 32;
    height = 32;
    xVelocity = 0;
    yVelocity = 0;
    collide = true;
}

AABB::~AABB(){

}

const int AABB::Left()    const{
    return left;
}

const int AABB::Up()  const{
    return up;
}

const int AABB::Width()   const{
    return width;
}

const int AABB::Height()  const{
    return height;
}

const int AABB::Right()   const{
    return left + width;
}

const int AABB::Down()    const{
    return up + height;
}

const float AABB::XVelocity() const{
    return xVelocity;
}

const float AABB::YVelocity() const{
    return yVelocity;
}

const int AABB::CenterX()    const{
    return left + width / 2;
}

const int AABB::CenterY()   const{
    return up + height / 2;
}

void AABB::SetXPosition(int x){
    left = x;
}

void AABB::SetYPosition(int y){
    up = y;
}

void AABB::SetPosition(int x, int y){
    left = x;
    up = y;
}

void AABB::SetWidth(int w){
    width = w;
}

void AABB::SetHeight(int h){
    height = h;
}

void AABB::SetXVelocity(float v){
    xVelocity = v;
}

void AABB::SetYVelocity(float v){
    yVelocity = v;
}

const bool AABB::Collision(const AABB& Other)   const{
    if(Other.Up() > Down() || Other.Down() < up
       || Other.Left() > Right() || Other.Right() < left)
       return false;
    return true;
}

const bool AABB::WillDownCollision(const AABB& Other)   const{
    if(yVelocity > 0)
        if(Down()+yVelocity >= Other.Up() && up < Other.Up())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
                return true;
    return false;
}

const bool AABB::WillUpCollision(const AABB& Other) const{
    if(yVelocity < 0)
        if(up + yVelocity <= Other.Down() && Down() > Other.Down())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
                return true;
    return false;
}


const bool AABB::WillCollision(const AABB& Other)   const{
    if(Other.Up() > Down() + yVelocity || Other.Down() < up + yVelocity
       || Other.Left() > Right() + xVelocity || Other.Right() < left + xVelocity)
       return false;

    else
        return true;
}

void AABB::Collide(const AABB& Other){
    if(!collide)
        return;

    if(yVelocity > 0)
        if(Down()+yVelocity >= Other.Up() && up < Other.Up())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right())){
                SetYPosition(Other.Up() - height - yVelocity);
                return;
            }


    if(yVelocity < 0)
        if(up + yVelocity <= Other.Down() && Down() > Other.Down())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right())){
                SetYPosition(Other.Down() - yVelocity);
                return;
            }


    if(xVelocity > 0)
        if(Right() + xVelocity >= Other.Left() && left < Other.Left())
            if((up + yVelocity > Other.Up() && Down() + yVelocity < Other.Down()) || (Down() + yVelocity > Other.Up() && up + yVelocity < Other.Up()) || (up + yVelocity < Other.Down() && Down() + yVelocity > Other.Down()) || (Down() + yVelocity > Other.Down() && up + yVelocity < Other.Up())){
                SetXPosition(Other.Left() - width - xVelocity);
                return;
            }


    if(xVelocity < 0)
        if(left + xVelocity <= Other.Right() && Right() > Other.Right())
            if((up + yVelocity > Other.Up() && Down() + yVelocity < Other.Down()) || (Down() + yVelocity > Other.Up() && up + yVelocity < Other.Up()) || (up + yVelocity < Other.Down() && Down() + yVelocity > Other.Down()) || (Down() + yVelocity > Other.Down() && up + yVelocity < Other.Up())){
                SetXPosition(Other.Right() - xVelocity);
                return;
            }
}

void AABB::Move(){
    SetPosition(left + xVelocity, up + yVelocity);
}

const bool AABB::Collides() const{
    return collide;
}

void AABB::SetCollide(bool b){
    collide = b;
}

