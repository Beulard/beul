#include "AABB.hpp"

AABB::AABB(){
    left = 0;
    up = 0;
    width = 32;
    height = 32;
    xVelocity = 0;
    yVelocity = 0;
    xAcceleration = 0;
    yAcceleration = 0;
    maxXVelocity = 5.f;
    minXVelocity = -5.f;
}

AABB::~AABB(){

}

const float AABB::Left()    const{
    return left;
}

const float AABB::Up()  const{
    return up;
}

const float AABB::Width()   const{
    return width;
}

const float AABB::Height()  const{
    return height;
}

const float AABB::Right()   const{
    return left + width;
}

const float AABB::Down()    const{
    return up + height;
}

const float AABB::XVelocity() const{
    return xVelocity;
}

const float AABB::YVelocity() const{
    return yVelocity;
}

const float AABB::CenterX()    const{
    return left + width / 2;
}

const float AABB::CenterY()   const{
    return up + height / 2;
}

void AABB::SetXPosition(float x){
    left = x;
}

void AABB::SetYPosition(float y){
    up = y;
}

void AABB::SetPosition(float x, float y){
    left = x;
    up = y;
}

void AABB::SetWidth(float w){
    width = w;
}

void AABB::SetHeight(float h){
    height = h;
}

void AABB::SetXAcceleration(float x){
    xAcceleration = x;
}

void AABB::SetYAcceleration(float y){
    yAcceleration = y;
}

void AABB::SetXVelocity(float v){
    xVelocity = v;
}

void AABB::SetYVelocity(float v){
    yVelocity = v;
}

const bool AABB::DownCollision(const AABB& Other)   const{
    if(Down() >= Other.Up() && up < Other.Up())
        if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
            return true;

    return false;
}

const bool AABB::UpCollision(const AABB& Other) const{
    if(up <= Other.Down() && Down() > Other.Down())
        if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
            return true;
    return false;
}

const bool AABB::RightCollision(const AABB& Other)  const{
    if(Right() >= Other.Left() && left < Other.Left())
        if((up > Other.Up() && Down() < Other.Down()) || (up < Other.Up() && Down() > Other.Down()) || (up < Other.Up() && Down() > Other.Up()) || (up < Other.Down() && Down() > Other.Down()))
            return true;
    return false;
}

const bool AABB::LeftCollision(const AABB& Other)   const{
    if(left <= Other.Right() && Right() > Other.Right())
        if((up > Other.Up() && Down() < Other.Down()) || (up < Other.Up() && Down() > Other.Down()) || (up < Other.Up() && Down() > Other.Up()) || (up < Other.Down() && Down() > Other.Down()))
            return true;
    return false;
}

const bool AABB::Collision(const AABB& Other)   const{
    if(Down() >= Other.Up() && up <= Other.Down() && left <= Other.Right() && Right() >= Other.Left())
        return true;
    return false;
}

const bool AABB::WillDownCollision(const AABB& Other)   const{
    if(Down() + yVelocity + yAcceleration >= Other.Up() && up < Other.Up())
        if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
            return true;

    return false;
}

const bool AABB::WillUpCollision(const AABB& Other) const{
    if(up + yVelocity <= Other.Down() && Down() > Other.Down())
        if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right()))
            return true;
    return false;
}

const bool AABB::WillRightCollision(const AABB& Other)  const{
    if(Right() + xVelocity >= Other.Left() && left < Other.Left())
        if((up > Other.Up() && Down() < Other.Down()) || (up < Other.Up() && Down() > Other.Down()) || (up < Other.Up() && Down() > Other.Up()) || (up < Other.Down() && Down() > Other.Down()))
            return true;
    return false;
}

const bool AABB::WillLeftCollision(const AABB& Other)   const{
    if(left + xVelocity <= Other.Right() && Right() > Other.Right())
        if((up > Other.Up() && Down() < Other.Down()) || (up < Other.Up() && Down() > Other.Down()) || (up < Other.Up() && Down() > Other.Up()) || (up < Other.Down() && Down() > Other.Down()))
            return true;
    return false;
}


const bool AABB::WillCollision(const AABB& Other)   const{
    /*if(Other.Up() > Down() + yVelocity + yAcceleration || Other.Down() < up + yVelocity + yAcceleration
       || Other.Left() > Right() + xVelocity || Other.Right() < left + xVelocity)*/
    //if(WillDownCollision(Other) || WillUpCollision(Other) || WillLeftCollision(Other) || WillRightCollision(Other))
    if(Down() + yVelocity >= Other.Up() && up + yVelocity <= Other.Down() && left + xVelocity <= Other.Right() && Right() + xVelocity >= Other.Left())
       return true;

    else
        return false;
}

void AABB::Collide(const AABB& Other){
    if(!Collides() || !Other.Collides())
        return;

    if(yVelocity > 0)
        if(Down() + yVelocity + yAcceleration >= Other.Up() && up < Other.Up())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right())){
                //SetYPosition(Other.Up() - height - yVelocity - yAcceleration);
                SetYPosition(up + (Other.Up() - Down()));
                yVelocity = 0.f;
                yAcceleration = 0.f;
                return;
            }


    if(yVelocity < 0)
        if(up + yVelocity + yAcceleration <= Other.Down() && Down() > Other.Down())
            if((left > Other.Left() && Right() < Other.Right()) || (Right() > Other.Left() && left < Other.Left()) || (left < Other.Right() && Right() > Other.Right()) || (left < Other.Left() && Right() > Other.Right())){
                //SetYPosition(Other.Down() - yVelocity - yAcceleration);
                SetYPosition(up + (Other.Down() - up));
                yVelocity = 0.f;
                yAcceleration = 0.f;
                return;
            }


    if(xVelocity + xAcceleration > 0)
        if(Right() + xVelocity + xAcceleration >= Other.Left() && left < Other.Left())
            if((up + yVelocity > Other.Up() && Down() + yVelocity < Other.Down()) || (Down() + yVelocity > Other.Up() && up + yVelocity < Other.Up()) || (up + yVelocity < Other.Down() && Down() + yVelocity > Other.Down()) || (Down() + yVelocity > Other.Down() && up + yVelocity < Other.Up())){
                SetXPosition(left + (Other.Left() - Right()));
                xVelocity = 0.f;
                xAcceleration = 0.f;
                //SetXPosition(Other.Left() - width - xVelocity - xAcceleration);
                return;
            }


    if(xVelocity + xAcceleration < 0)
        if(left + xVelocity + xAcceleration <= Other.Right() && Right() > Other.Right())
            if((up + yVelocity > Other.Up() && Down() + yVelocity < Other.Down()) || (Down() + yVelocity > Other.Up() && up + yVelocity < Other.Up()) || (up + yVelocity < Other.Down() && Down() + yVelocity > Other.Down()) || (Down() + yVelocity > Other.Down() && up + yVelocity < Other.Up())){
                SetXPosition(left + (Other.Right() - left));
                xVelocity = 0.f;
                xAcceleration = 0.f;
                //SetXPosition(Other.Right() - xVelocity - xAcceleration);
                return;
            }
}

void AABB::Accelerate(){
    xVelocity *= 1.05f;
    yVelocity *= 1.05f;
}

void AABB::AccelerateLeft(){
    if(xAcceleration == 0)
        xAcceleration = -0.2f;
}

void AABB::AccelerateRight(){
    if(xAcceleration == 0)
        xAcceleration = 0.2f;
}

void AABB::Decelerate(){
    xVelocity *= 0.6f;

    if((xVelocity > 0.f && xVelocity <= 0.1f) || (xVelocity < 0.f && xVelocity > 0.1f))
        xVelocity = 0.f;

    xAcceleration = 0.f;
}

void AABB::Fall(){
    yVelocity += gravity;
}

void AABB::Move(){
    xVelocity += xAcceleration;
    yVelocity += yAcceleration;
    if(xVelocity > 10.f)
        xVelocity = 10.f;
    if(xVelocity < -10.f)
        xVelocity = -10.f;


    SetPosition(left + xVelocity, up + yVelocity);
    xAcceleration = 0.f;
    yAcceleration = 0.f;
}

/*void AABB::MissileMove(){
    SetPosition(left + xVelocity, up + yVelocity);
}*/

const bool AABB::Collides() const{
    return true;
}

