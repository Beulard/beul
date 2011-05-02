#ifndef BEUL_ROCKET
#define BEUL_ROCKET

#include "Missile.hpp"
#include "Explosion.hpp"

class Rocket : public Missile{
    public:
        Rocket();
        Rocket(unsigned int radius);
        ~Rocket();

        virtual Missile* Clone();

        virtual void onCollision(World& w, unsigned int thisIndex, unsigned int colX, unsigned int colY);

    protected:
        unsigned int explosionRadius;

};

#endif // BEUL_ROCKET
