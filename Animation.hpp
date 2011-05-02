#ifndef BEUL_ANIMATION
#define BEUL_ANIMATION

#include "Frame.hpp"

class Animation
{
    public:
        Animation();
        ~Animation();

        void AddFrame(const Frame& F);
        void Draw(sf::RenderWindow& W);
        const Frame* GetFrame(unsigned int index)   const;
        void Animate(float time);

        void SetPosition(int x, int y);

        void Play();
        void Pause();
        void Stop();
        void Reset();


    private:
        std::vector<Frame*> Frames;
        unsigned int currentFrame;
        bool paused;
        float totalTime;
};

#endif // BEUL_ANIMATION
