#ifndef BEUL_WEAPON
#define BEUL_WEAPON

#include "Item.hpp"
#include "Missile.hpp"

class Weapon : public Item{
    public:
        Weapon();
        virtual ~Weapon() = 0;

        //virtual void onUse(World& w, int targetX, int targetY) = 0;

        void Reload(float frameTime);

    protected:
        MissileID Ammo;
        float currentTime;
        float reloadTime;
        bool ready;
};

#endif // BEUL_WEAPON
