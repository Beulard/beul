#ifndef BEUL_ITEM
#define BEUL_ITEM

#include "AABB.hpp"
#include "TileSprite.hpp"

class Player;
class Item;
class World;




class ItemAppearances : public BlockAppearances{
    public:
        ItemAppearances(bool);
};

extern ItemAppearances IA;

enum ItemID{
    APPLE = 0,
    ROCKETLAUNCHER = 1
};

class ItemList{
    public:
        void RegisterItem(Item* i);
        Item* operator[](unsigned int index);
        std::vector<Item*> items;
};

extern ItemList itemList;


class Item : public AABB{
    public:
        Item();
        virtual ~Item() = 0;

        virtual Item* Clone() = 0;

        void Draw(sf::RenderWindow& W);

        const unsigned int GetID()    const;

        void SetPosition(float x, float y);

        virtual void onGet(World& w) = 0;
        //virtual void onUse(World& w) = 0;
        virtual void onUse(World& w, int targetX, int targetY) = 0;



    protected:
        ItemID id;
        sf::Sprite* appearance;
};

#endif // BEUL_ITEM
