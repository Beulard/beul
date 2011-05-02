#ifndef BEUL_EXPLOSION
#define BEUL_EXPLOSION

#include "Map.hpp"

class Explosion
{
    public:
        Explosion(World& w, unsigned int colX, unsigned int colY, unsigned int radius);
        ~Explosion();

        void Explode(World& w, int colX, int colY);

    private:
        unsigned int Radius;
};

#endif // BEUL_EXPLOSION
