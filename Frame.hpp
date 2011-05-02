#ifndef BEUL_FRAME
#define BEUL_FRAME

#include "SFML/Graphics.hpp"
#include <iostream>


class Frame{
    public:
        Frame();
        Frame(sf::Sprite& s, float fTime);
        ~Frame();

        void SetFrameTime(float fTime);
        void Draw(sf::RenderWindow& W);
        const float GetFrameTime()  const;

        void SetPosition(int x, int y);

    private:
        sf::Sprite* sprite;
        float time;
};

#endif // BEUL_FRAME
