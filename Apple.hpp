#ifndef BEUL_APPLE
#define BEUL_APPLE

#include "Item.hpp"
#include "World.hpp"


class Apple : public Item{
    public:
        Apple();
        ~Apple();

        virtual Item* Clone();

        virtual void onGet(World& w);
        virtual void onUse(World& w, int targetX, int targetY);

};

#endif // BEUL_APPLE
