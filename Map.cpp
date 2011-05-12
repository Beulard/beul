#include "Map.hpp"

std::string IntToString(const int i){
    std::ostringstream oss;
    oss << i;
    return std::string(oss.str());
}

Map::Map(){

}

Map::Map(const Grid& g){
    needRePlacing = true;
    nbrColumns = g.GetNbrColumns();
    nbrTilesPerColumn = g.GetNbrBoxesPerColumn();
    elements.push_back(std::vector<TileAABB*>());
}

Map::Map(unsigned int width, unsigned int height){
    needRePlacing = true;
    nbrColumns = 758;
    nbrTilesPerColumn = height / TILES_SIZE;
    elements.push_back(std::vector<TileAABB*>());
}

Map::Map(const Grid& g, MapManager& mm){
    *this = Map(g);
}

Map::~Map(){
    for(unsigned int i=0; i<elements.size(); ++i)
        for(unsigned int j=0; j<elements[i].size(); ++j)
            if(TileExists(i, j))
                delete elements[i][j];
    //for(unsigned int i=0; i<items.size(); ++i)
       // delete items[i];
}

void Map::GenerateRandomElements(){
    srand(time(NULL));
    for(unsigned int i=0; i<nbrColumns; ++i){
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){

            //unsigned int nbr = rand() % 12;
            //if(nbr <= 6)
            //if(j < 12){
            if(j <= 14)
                AddElement(SKY);
            else if(j > 14)
                AddElement(EARTH);


        }
    }

    for(unsigned int i=nbrColumns - 1; i >= 1; --i){
        for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
            if(j < nbrTilesPerColumn - 2 && j >= 6){
                unsigned int nbr = rand() % 12;
                if(*GetAboveTile(i, j) == SKY && *GetTile(i, j) == EARTH){
                    if(nbr < 7){
                        ReplaceElementWith(i, j - 1, EARTH);
                    }
                }
            }
        }
    }

    for(unsigned int loop=0; loop<12; ++loop){
        for(unsigned int i=nbrColumns - 1; i >= 1; --i){
            for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
                unsigned int nbr = rand() % 12;
                if(j < nbrTilesPerColumn - 1){
                    if(*GetLeftTile(i, j) == EARTH && *GetBelowTile(i, j) == SKY && nbr < 2){
                        ReplaceElementWith(i, j + 1, EARTH);
                    }
                }
            }
        }

        for(int i=nbrColumns - 1; i >= 0; --i){
            for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
                unsigned int nbr = rand() % 12;
                if(j < nbrTilesPerColumn - 1 && static_cast<unsigned int>(i) < nbrColumns - 1){
                    if(*GetRightTile(i, j) == EARTH && *GetBelowTile(i, j) == SKY && nbr < 2){
                        ReplaceElementWith(i, j + 1, EARTH);
                    }
                }
            }
        }
        /*for(int i=nbrColumns - 1; i >= 0; --i){
            for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
        if(i > 3 && i < nbrColumns - 4 && j > 3 && j < nbrTilesPerColumn - 4)
                if(elements[i][j + 1] == EARTH && elements[i][j + 2] == EARTH && elements[i + 1][j + 2] == EARTH && elements[i - 1][j + 2] == EARTH
                   && elements[i][j] == SKY && elements[i + 1][j] == SKY && elements[i - 1][j] == SKY && elements[i + 1][j + 1] == SKY && elements[i - 1][j + 1] == SKY){
                       delete elements[i][j + 1];
                       elements[i][j + 1] = new TileAABB(SKY);
                   }
            }
        }*/

    }

    for(int i=nbrColumns - 1; i >= 0; --i){
        for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
            if(static_cast<unsigned int>(i) > 1 && static_cast<unsigned int>(i) < nbrColumns - 2 && j > 1 && j < nbrTilesPerColumn - 3){
                if(*GetTile(i, j) == EARTH && *GetTile(i + 1, j + 1) == EARTH && *GetTile(i - 1, j + 1) == EARTH &&
                    *GetTile(i, j + 2) == EARTH && *GetBelowTile(i, j) == SKY){
                    ReplaceElementWith(i, j + 1, EARTH);
                }
            }
        }
    }



    for(unsigned int i=0; i<nbrColumns; ++i){
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            if(j > 1){
                if(*GetAboveTile(i, j) == SKY && *GetTile(i, j) == EARTH){
                        ReplaceElementWith(i, j, GRASS);
                }
            }
        }
    }
    for(unsigned int i=0; i<nbrColumns; ++i)
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            unsigned int nbr = rand() % 100;
            if(*GetTile(i, j) == SKY && j > 6 && nbr > 97)
                AddItem(APPLE, i, j);
        }

    for(unsigned int i=0; i<nbrColumns; ++i)
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            if(*GetTile(i, j) == SKY && j > 13)
                ReplaceElementWith(i, j, LAVA);
            if(*GetTile(i, j) == GRASS && *GetAboveTile(i, j) == LAVA)
                ReplaceElementWith(i, j, EARTH);
        }

    /*for(unsigned int i=0; i<nbrColumns; ++i){
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            if(elements[i][j] != SKY){
                if(i < nbrColumns - 1 && i > 0 && j < nbrTilesPerColumn - 1 && j > 0){
                    TileAABB* t = dynamic_cast<TileAABB*>(elements[i][j]);
                    if(GetAboveTile(i, j) == SKY)
                        t->CS |= UP;
                    if(GetBelowTile(i, j) == SKY)
                        t->CS |= DOWN;
                    if(GetLeftTile(i, j) == SKY)
                        t->CS |= LEFT;
                    if(GetRightTile(i, j) == SKY)
                        t->CS |= RIGHT;
                }
            }
            else
                t->CS = NONE;
        }
    }*/
//    std::cout << "dur dur" << std::endl;
    //ReplaceElementWith(5, 10, LAVA);
//    std::cout << "hur hur" << std::endl;
}

void Map::NeedsRePlacing(bool b){
    needRePlacing = b;
}

void Map::RePlaceElements(sf::RenderWindow& W){
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(TileExists(i, j))
                privGetTile(i, j)->SetPosition(i*TILES_SIZE, j*TILES_SIZE);
        }
    }
}

void Map::AddElement(unsigned int ID){
    if(elements.back().size() > 0)
        if(elements.back().back()->GetXPosition() + 33 > 1024 && elements.back().back()->GetYPosition() + 33 > 576)
            return;
    if(elements.back().size() + 1 > nbrTilesPerColumn)
        elements.push_back(std::vector<TileAABB*>());
    elements.back().push_back(tileList[ID]);
}

void Map::DeleteElement(unsigned int x, unsigned int y){
    if(TileExists(x, y)){
        delete privGetTile(x, y);
        elements[x].erase(elements[x].begin() + y);
    }
}

void Map::ReplaceElementWith(unsigned int x, unsigned int y, unsigned int ID){
    if(TileExists(x, y)){
        int ax = GetTile(x, y)->Left();
        int ay = GetTile(x, y)->Up();
        delete privGetTile(x, y);
        elements[x][y] = tileList[ID];
        privGetTile(x, y)->SetPosition(ax, ay);
    }
}

void Map::AddItem(unsigned int ID, int xPos, int yPos){
    items.push_back(itemList[ID]);
    items.back()->SetPosition(xPos*TILES_SIZE, yPos*TILES_SIZE);
}

void Map::DeleteItem(unsigned int index){
    delete items[index];
    items.erase(items.begin() + index);
}

bool Map::TileExists(int x, int y)  const{
    if((x >= 0 && y >= 0 && x < elements.size() && y < elements[0].size())/* || elements[x][y] != NULL*/)
        return true;
    return false;
}

const TileAABB* Map::GetTile(int x, int y)  const{
    try{
        if(TileExists(x, y))
            return elements[x][y];
        else
            throw 0;
    }

    catch(int){
        std::cerr << "Can't access tile 'elements[" << IntToString(x) << "][" << IntToString(y) << "]'. Returning elements[0][0]." << std::endl;
        return elements[0][0];
    }
}

const TileAABB* Map::GetAboveTile(int x, int y)   const{
    try{
        if(TileExists(x, y - 1))
            return elements[x][y - 1];
        throw std::string("Can't access tile above 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

const TileAABB* Map::GetLeftTile(int x, int y)    const{
    try{
        if(TileExists(x - 1, y))
            return elements[x - 1][y];
        throw std::string("Can't access tile left to 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

const TileAABB* Map::GetRightTile(int x, int y)   const{
    try{
        if(TileExists(x + 1, y))
        return elements[x + 1][y];
        throw std::string("Can't access tile right to 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

const TileAABB* Map::GetBelowTile(int x, int y)   const{
    try{
        if(TileExists(x, y + 1))
            return elements[x][y + 1];
        throw std::string("Can't access tile below 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

TileAABB* Map::privGetTile(int x, int y){
    try{
        if(TileExists(x, y))
            return elements[x][y];
        throw std::string("Can't access tile 'elements[" + IntToString(x)+ "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

TileAABB* Map::privGetAboveTile(int x, int y){
    try{
        if(TileExists(x, y - 1))
            return elements[x][y - 1];
        throw std::string("Can't access tile above 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

TileAABB* Map::privGetLeftTile(int x, int y){
    try{
        if(TileExists(x - 1, y))
            return elements[x - 1][y];
        throw std::string("Can't access tile left to 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

TileAABB* Map::privGetRightTile(int x, int y){
    try{
        if(TileExists(x + 1, y))
            return elements[x + 1][y];
        throw std::string("Can't access tile right to 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

TileAABB* Map::privGetBelowTile(int x, int y){
    try{
        if(TileExists(x, y + 1))
            return elements[x][y + 1];
        throw std::string("Can't access tile below 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
    }
}

const unsigned int Map::GetNbrColumns() const{
    return nbrColumns;
}

const unsigned int Map::GetNbrTilesPerColumn()  const{
    return nbrTilesPerColumn;
}

void Map::Draw(sf::RenderWindow& W){
    if(needRePlacing){
        RePlaceElements(W);
        needRePlacing = false;
    }
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            TileAABB* t = elements[i][j];
            if(t->Right() >= W.GetView().GetRect().Left && t->Left() <= W.GetView().GetRect().Right)
                if(TileExists(i, j))
                    elements[i][j]->Draw(W);
        }
    }
    for(unsigned int i=0; i<items.size(); ++i)
        if(items[i]->Right() >= W.GetView().GetRect().Left && items[i]->Left() <= W.GetView().GetRect().Right)
            items[i]->Draw(W);
}

/*void Map::GetCollisions(std::vector<unsigned int>& iCollisions, std::vector<unsigned int>& jCollisions){
    iCollisions.clear();
    jCollisions.clear();
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(elements[i][j] != SKY){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if((GetAboveTile(i, j) == SKY || GetBelowTile(i, j) == SKY || GetRightTile(i, j) == SKY || GetLeftTile(i, j) == SKY)){
                            iCollisions.push_back(i);
                            jCollisions.push_back(j);
                        }
                    }
                    else{
                        iCollisions.push_back(i);
                        jCollisions.push_back(j);
                    }
                }
                else{
                    iCollisions.push_back(i);
                    jCollisions.push_back(j);
                }
            }
        }
    }
}*/

/*void Map::FastGetCollisions(const Player& p, std::vector<unsigned int>& iCollisions, std::vector<unsigned int>& jCollisions){
    iCollisions.clear();
    jCollisions.clear();
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(dynamic_cast<TileAABB*>(elements[i][j]) != SKY){
                if(p.GetCollisionLimit()->WillCollision(*dynamic_cast<TileAABB*>(elements[i][j]))){
                    iCollisions.push_back(i);
                    jCollisions.push_back(j);
                }
            }
        }
    }
}*/

/*void Map::ComputeCollisions(){
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            //if(elements[i][j]->Collides()){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if(!GetAboveTile(i, j)->Collides() || !GetBelowTile(i, j)->Collides() || !GetRightTile(i, j)->Collides() || !GetLeftTile(i, j)->Collides()){
                            privGetTile(i, j)->SetCollide(true);
                        }
                        else
                            privGetTile(i, j)->SetCollide(false);
                    }
                    else{
                        privGetTile(i, j)->SetCollide(true);
                    }
                }
                else{
                    privGetTile(i, j)->SetCollide(true);
                }
            //}
            if(*GetTile(i, j) == SKY)
                privGetTile(i, j)->SetCollide(false);
        }
    }
    /*collisions.clear();
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(elements[i][j]->Collides()){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if(!GetAboveTile(i, j)->Collides() || !GetBelowTile(i, j)->Collides() || !GetRightTile(i, j)->Collides() || !GetLeftTile(i, j)->Collides()){
                            collisions.push_back(&elements[i][j]);
                        }
                    }
                    else{
                        collisions.push_back(&elements[i][j]);
                    }
                }
                else{
                    collisions.push_back(&elements[i][j]);
                }
            }
        }
    }*/
//}

/*void Map::ReComputeCollisions(){
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(elements[i][j]->Collides()){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if(!GetAboveTile(i, j)->Collides() || !GetBelowTile(i, j)->Collides() || !GetRightTile(i, j)->Collides() || !GetLeftTile(i, j)->Collides()){
                            collisions.push_back(&elements[i][j]);
                        }
                    }
                    else{
                        collisions.push_back(&elements[i][j]);
                    }
                }
                else{
                    collisions.push_back(&elements[i][j]);
                }
            }
        }
    }
}*/

/*const std::vector<TileAABB**> Map::GetCollisions()   cons{
    return collisions;
}*/


const std::vector< std::vector< TileAABB* > >& Map::GetElements()   const{
    return elements;
}

const std::vector< Item* >& Map::GetItems() const{
    return items;
}

const unsigned int Map::GetNbrElements()    const{
    unsigned int size = 0;
    for(unsigned int i=0; i<elements.size(); ++i)
        size += elements[i].size();
    return size;
}

