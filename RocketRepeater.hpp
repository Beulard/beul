#ifndef BEUL_ROCKETREPEATER
#define BEUL_ROCKETREPEATER

#include "RocketLauncher.hpp"


class RocketRepeater : public RocketLauncher{
    public:
        RocketRepeater();
        ~RocketRepeater();

        virtual Item* Clone();

        virtual void onGet(World& w);
};

#endif // BEUL_ROCKETREPEATER
