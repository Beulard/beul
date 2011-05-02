#ifndef BEUL_MAPMANAGER
#define BEUL_MAPMANAGER
#include <fstream>


class MapManager
{
    public:
        MapManager();
        MapManager(const char* file);   //TODO
        ~MapManager();

        void LoadFromFile(const char* file);    //TODO

    private:
        std::fstream file;
};

#endif // BEUL_MAPMANAGER
