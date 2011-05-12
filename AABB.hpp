#ifndef BEUL_AABB
#define BEUL_AABB

#include <iostream>

const float gravity = 0.5f;

class AABB{
    public:
        AABB();
        virtual ~AABB();

        const float Left()    const;
        const float Up()  const;
        const float Width()   const;
        const float Height()  const;
        const float Right()   const;
        const float Down()    const;
        const float XVelocity() const;
        const float YVelocity() const;

        const float CenterX()  const;
        const float CenterY()  const;

        void SetXPosition(float x);
        void SetYPosition(float y);
        virtual void SetPosition(float x, float y);
        void SetWidth(float w);
        void SetHeight(float h);

        void SetXAcceleration(float x);
        void SetYAcceleration(float y);

        void SetMaxXVelocity(float x);
        void SetMaxYVelocity(float y);

        void SetAcceleration(float x, float y);


        void Accelerate();
        void AccelerateRight();
        void AccelerateLeft();
        void Decelerate();

        void Fall();

        virtual void Move();

        virtual const bool Collides()   const;


        const bool UpCollision(const AABB& Other)   const;
        const bool DownCollision(const AABB& Other) const;
        const bool RightCollision(const AABB& Other)    const;
        const bool LeftCollision(const AABB& Other) const;
        const bool Collision(const AABB& Other) const;
        const bool WillLeftCollision(const AABB& Other) const;
        const bool WillRightCollision(const AABB& Other)    const;
        const bool WillDownCollision(const AABB& Other) const;
        const bool WillUpCollision(const AABB& Other)   const;
        const bool WillCollision(const AABB& Other) const;
        void Collide(const AABB& Other);

        void SetXVelocity(float v);
        void SetYVelocity(float v);

    protected:


        float maxXVelocity;
        float minXVelocity;

        float left;
        float up;
        float width;
        float height;
        float xVelocity;
        float yVelocity;
        float xAcceleration;
        float yAcceleration;
};

#endif // BEUL_AABB
