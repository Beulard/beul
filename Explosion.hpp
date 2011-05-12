#ifndef BEUL_EXPLOSION
#define BEUL_EXPLOSION

#include "Map.hpp"

class Params{
    public:
        virtual ~Params(){

        }
};


class DoNothingParams : public Params{

};


class ExplodeParams : public Params{
    public:
        ExplodeParams(){}
        World* w;
        unsigned int colX;
        unsigned int colY;
        unsigned int index;
        unsigned int rad;
};


class DeleteMissileParams : public Params{
    public:
        DeleteMissileParams(){}
        World* w;
        unsigned int index;
};


class ExplosionReactionParams{
    public:
        ExplosionReactionParams();
        ExplosionReactionParams(bool);

        Params* operator[](unsigned int index);

    private:
        std::vector<Params*> params;
};

extern ExplosionReactionParams ERP;


void DoNothing(Params*);
void Explode(Params*);
void DeleteMissile(Params*);



class Explosion{
    public:
        Explosion(World& w, unsigned int colX, unsigned int colY, unsigned int radius);
        ~Explosion();


    private:
        void Explode(World& w, int colX, int colY);

        unsigned int Radius;
};

#endif // BEUL_EXPLOSION
