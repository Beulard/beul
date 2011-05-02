#ifndef BEUL_TILESPRITE
#define BEUL_TILESPRITE

#include "Tile.hpp"



struct Images{
    Images();
    Images(bool);

    sf::Image skyimg;
    sf::Image grassimg;
    sf::Image earthimg;
    sf::Image appleimg;
    sf::Image rocketlauncherimg;
    sf::Image rocketimg;
};

extern Images I;

class BlockAppearances{
    public:
        BlockAppearances();
        BlockAppearances(bool);
        ~BlockAppearances();

        sf::Sprite& operator[](unsigned int ID);

        void push_back(const sf::Image& i);

    protected:
        std::vector<sf::Sprite> a;
};

extern BlockAppearances BA;

//static std::vector<sf::Sprite> BlockAppearances;



class TileSprite : public Tile{
    public:
        TileSprite();
        TileSprite(unsigned int ID);
        ~TileSprite();

        void SetAppearance(sf::Sprite& a);
        const sf::Sprite* GetAppearance() const;

        void Draw(sf::RenderWindow& W);

    protected:
        sf::Sprite* appearance;
};

#endif // BEUL_TILESPRITE
