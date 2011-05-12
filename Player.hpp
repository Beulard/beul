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

        void Move();

        void SetWeapon(unsigned int ID);
        const unsigned int GetWeaponID()    const;

        void SetAnimation(Animation& a);
        void Draw(sf::RenderWindow& W);


        void UseWeapon(World& w, int targetX, int targetY);
        void Reload(float frameTime);

        void AddLife();
        const int GetLives()    const;
        void Die();

        void AddItem(unsigned int ID);
        void SetWeapon(const Weapon& w);

    private:
        Animation* Anim;
        Weapon* weapon;
        int lives;
        int spawnPointX;
        int spawnPointY;
};

#endif // BEUL_PLAYER
