#include "Player.hpp"
#include "World.hpp"

Player::Player(){
    AABB::SetPosition(400, 150);
    xVelocity = 0;
    height = 50;
    width = 50;
    lives = 3;
    weapon = NULL;
    spawnPointX = left;
    spawnPointY = up;
}

Player::~Player(){
    if(weapon != NULL)
        delete weapon;
}

void Player::SetWeapon(unsigned int ID){
    if(weapon != NULL)
        delete weapon;

    weapon = dynamic_cast<Weapon*>(itemList[ID]);
}

const unsigned int Player::GetWeaponID()    const{
    if(weapon == NULL){
        std::cout << "Player has no weapon" << std::endl;
        return 666;
    }

    return weapon->GetID();
}

void Player::UseWeapon(World& w, int targetX, int targetY){
    if(weapon == NULL)
        return;
    weapon->onUse(w, targetX, targetY);
}

void Player::Reload(float frameTime){
    if(weapon == NULL)
        return;
    weapon->Reload(frameTime);
}

void Player::DropWeapon(World& w){
    if(weapon != NULL){
        w.map->AddItem(weapon->GetID(), CenterX(), CenterY());
        delete weapon;

        weapon = NULL;
    }
}

void Player::Move(){
    AABB::Move();
}

void Player::SetAnimation(Animation& a){
    Anim = &a;
}

void Player::AddLife(){
    lives++;
}

const int Player::GetLives()    const{
    return lives;
}

void Player::Die(){
    lives--;
    //SetPosition(spawnPointX, spawnPointY);
    yVelocity = -20.f;
}


void Player::Draw(sf::RenderWindow& W){
    if(lives > 3)
        lives = 3;
    Anim->Animate(W.GetFrameTime());
    Anim->SetPosition(left, up);
    Anim->Draw(W);
}

/*void Player::SetWeapon(const Weapon& w){
    *inv.weapon = w;
}*/


/*void Player::SetAnim(const sf::Sprite& anim){
    *appearance = anim;
}*/

