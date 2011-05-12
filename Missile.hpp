#ifndef BEUL_MISSILE
#define BEUL_MISSILE

#include "Item.hpp"
#include "TileAABB.hpp"

class Missile;

enum MissileID{
    ROCKET = 0
};

class MissileAppearances : public BlockAppearances{
    public:
        MissileAppearances(bool);
};

extern MissileAppearances MA;

class MissileList{
    public:
        void RegisterMissile(Missile* m);
        Missile* operator[](unsigned int index);
        const unsigned int size()   const;
    private:
        std::vector<Missile*> missiles;
};

extern MissileList missileList;

class Missile : public TileAABB{
    public:
        Missile();
        virtual ~Missile() = 0;

        virtual Missile* Clone() = 0;

        virtual void onCollision(World& w, unsigned int colX, unsigned int colY, unsigned int thisIndex) = 0;

    protected:
        MissileID id;
};

#endif // BEUL_MISSILE
