#ifndef BEUL_ANIMATEDTILE
#define BEUL_ANIMATEDTILE

#include "TileAABB.hpp"
#include "Animation.hpp"

enum AnimatedTileID{
    ALAVA = 0
};

class FrameList{
    public:
        FrameList();
        FrameList(bool);
        Frame& operator[](unsigned int index);
        const unsigned int size() const;
    private:
        std::vector<Frame> frames;
};

extern FrameList frameList;

class AnimationList{
    public:
        AnimationList();
        AnimationList(bool);
        Animation& operator[](unsigned int index);
        const unsigned int size()   const;
    private:
        std::vector<Animation> anims;
};


extern AnimationList animationList;

class AnimatedTile : public TileAABB{
    public:
        AnimatedTile();
        ~AnimatedTile();

        virtual TileAABB* Clone() = 0;

        virtual void Draw(sf::RenderWindow& W);

        const Animation* GetAnim()  const;

        const unsigned int GetAnimationID()  const;

        virtual void onCollision(World& w);

    protected:
        Animation* anim;
        AnimatedTileID aid;
};

#endif // BEUL_ANIMATEDTILE
