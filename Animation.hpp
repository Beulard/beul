#ifndef BEUL_ANIMATION
#define BEUL_ANIMATION

#include "Frame.hpp"

class Animation
{
    public:
        Animation();
        Animation(const std::vector<Frame*>& frames);
        ~Animation();

        void AddFrame(Frame& F);
        void Draw(sf::RenderWindow& W);
        const Frame* GetFrame(unsigned int index)   const;
        void Animate(float time);

        void SetPosition(int x, int y);

        void Play();
        void Pause();
        void Stop();
        void Reset();

        const unsigned int size() const;
        unsigned int currentFrame;

    private:
        std::vector<Frame*> Frames;

        bool paused;
        float totalTime;
};

#endif // BEUL_ANIMATION
