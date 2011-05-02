#ifndef BEUL_TILE
#define BEUL_TILE
#include "SFML/Graphics.hpp"
#include <iostream>

enum TileAppearanceMode{
    INVISIBLE,
    VISIBLE
};

enum TileID{
    SKY = 0,
    EARTH = 1,
    GRASS = 2
};


class Tile{

    public:
        Tile();
        virtual ~Tile() = 0;

        virtual void Draw(sf::RenderWindow& W);
        virtual void SetPosition(int x, int y);
        const int GetXPosition()    const;
        const int GetYPosition()    const;

        const unsigned int GetID()    const;

        virtual void operator=(unsigned int ID);

    protected:
        TileID id;
        int xPosition;
        int yPosition;
};

#endif // BEUL_TILE
