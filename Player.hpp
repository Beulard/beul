#ifndef BEUL_PLAYER
#define BEUL_PLAYER

#include "Animation.hpp"
#include "Weapon.hpp"

extern ItemList itemList;

/*class Inventory{
    public:
        Inventory();
        ~Inventory();

        void SetWeapon(const Weapon& w);

    //private:
        Weapon* weapon;
};*/

class Player : public AABB{
    public:
        Player();
        ~Player();

        const AABB* GetCollisionLimit() const;
        void Move();

        void SetWeapon(unsigned int ID);
        const unsigned int GetWeaponID()    const;

        void SetAnimation(Animation& a);
        void Draw(sf::RenderWindow& W);


        void UseWeapon(World& w, int targetX, int targetY);
        void Reload(float frameTime);

        const int GetLives()    const;

        void AddItem(unsigned int ID);
        void SetWeapon(const Weapon& w);

        void operator--(int);

    private:
        AABB* CollisionLimit;
        Animation* Anim;
        Weapon* weapon;
        int lives;
};

#endif // BEUL_PLAYER
