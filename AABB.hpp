#ifndef BEUL_AABB
#define BEUL_AABB

#include <iostream>

class AABB{
    public:
        AABB();
        virtual ~AABB();

        const int Left()    const;
        const int Up()  const;
        const int Width()   const;
        const int Height()  const;
        const int Right()   const;
        const int Down()    const;
        const float XVelocity() const;
        const float YVelocity() const;

        const int CenterX()  const;
        const int CenterY()  const;

        void SetXPosition(int x);
        void SetYPosition(int y);
        void SetPosition(int x, int y);
        void SetWidth(int w);
        void SetHeight(int h);
        void SetXVelocity(float v);
        void SetYVelocity(float v);

        virtual void Move();

        const bool Collides()   const;
        void SetCollide(bool b);

        const bool Collision(const AABB& Other) const;
        const bool WillDownCollision(const AABB& Other) const;
        const bool WillUpCollision(const AABB& Other)   const;
        const bool WillCollision(const AABB& Other) const;
        void Collide(const AABB& Other);

    protected:
        int left;
        int up;
        int width;
        int height;
        float xVelocity;
        float yVelocity;
        bool collide;

};

#endif // BEUL_AABB
