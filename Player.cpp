#include "Player.hpp"

/////////////   Inventory   /////////////
/*Inventory::Inventory(){
    weapon = new Weapon(static_cast<Weapon&>(itemList[ROCKETLAUNCHER]));
}

Inventory::~Inventory(){
    delete weapon;
}

void Inventory::SetWeapon(const Weapon& w){
    *weapon = w;
}*/


///////////    Player    //////////////

Player::Player(){
    AABB::SetPosition(400, 150);
    xVelocity = 0;
    height = 50;
    width = 50;
    CollisionLimit = new AABB;
    CollisionLimit->SetXPosition(0);
    CollisionLimit->SetYPosition(0);
    CollisionLimit->SetWidth(120);
    CollisionLimit->SetHeight(120);
    lives = 3;
    weapon = NULL;
}

Player::~Player(){
    if(weapon != NULL)
        delete weapon;
}

void Player::SetWeapon(unsigned int ID){
    if(weapon != NULL)
        delete weapon;

    weapon = dynamic_cast<Weapon*>(itemList[ID]->Clone());
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



const AABB* Player::GetCollisionLimit() const{
    return CollisionLimit;
}

void Player::Move(){
    AABB::Move();
    CollisionLimit->SetPosition(left - 35, up - 35);
}

void Player::SetAnimation(Animation& a){
    Anim = &a;
}

const int Player::GetLives()    const{
    return lives;
}

void Player::operator--(int){
    lives--;
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

