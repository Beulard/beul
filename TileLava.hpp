#ifndef BEUL_TILELAVA
#define BEUL_TILELAVA

#include "AnimatedTile.hpp"


class TileLava : public AnimatedTile{
    public:
        TileLava();
        ~TileLava();

        virtual TileAABB* Clone();

        virtual void Draw(sf::RenderWindow& W);

        void onCollision(World& w);
        void onCollisionWithRocket(World& w, unsigned int indexX, unsigned int indexY, unsigned int source);

        virtual const bool Collides()   const;

        virtual void SetPosition(float x, float y);
};

#endif // BEUL_TILELAVA
