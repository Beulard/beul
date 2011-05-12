#ifndef BEUL_ANIMATION
#define BEUL_ANIMATION

#include "Frame.hpp"

class Animation{
    public:
        Animation();
        Animation(const std::vector<Frame>& frames);
        Animation(const Animation& copy);
        ~Animation();

        void AddFrame(Frame& F);
        void Draw(sf::RenderWindow& W);
        const Frame& GetFrame(unsigned int index)   const;
        const std::vector<Frame>& GetFrames()   const;
        const unsigned int size()   const;
        void Animate(float time);

        void SetPosition(int x, int y);

        void Play();
        void Pause();
        void Stop();
        void Reset();
        unsigned int currentFrame;

    private:
        std::vector<Frame> Frames;

        bool paused;
        float totalTime;
};

#endif // BEUL_ANIMATION
