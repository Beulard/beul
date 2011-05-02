#ifndef BEUL_ROCKETLAUNCHER
#define BEUL_ROCKETLAUNCHER

#include "Weapon.hpp"
#include "Player.hpp"
#include "World.hpp"

class RocketLauncher : public Weapon{
    public:
        RocketLauncher();
        ~RocketLauncher();

        virtual Item* Clone();

        virtual void onGet(World& w);
        virtual void onUse(World& w, int targetX, int targetY);

    private:
};

#endif // BEUL_ROCKETLAUNCHER
