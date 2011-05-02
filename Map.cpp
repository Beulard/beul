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
                if(GetAboveTile(i, j)->GetID() == SKY && GetTile(i, j)->GetID() == EARTH){
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
                    if(GetLeftTile(i, j)->GetID() == EARTH && GetBelowTile(i, j)->GetID() == SKY && nbr < 2){
                        ReplaceElementWith(i, j + 1, EARTH);
                    }
                }
            }
        }

        for(int i=nbrColumns - 1; i >= 0; --i){
            for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
                unsigned int nbr = rand() % 12;
                if(j < nbrTilesPerColumn - 1 && static_cast<unsigned int>(i) < nbrColumns - 1){
                    if(GetRightTile(i, j)->GetID() == EARTH && GetBelowTile(i, j)->GetID() == SKY && nbr < 2){
                        ReplaceElementWith(i, j + 1, EARTH);
                    }
                }
            }
        }
        /*for(int i=nbrColumns - 1; i >= 0; --i){
            for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
        if(i > 3 && i < nbrColumns - 4 && j > 3 && j < nbrTilesPerColumn - 4)
                if(elements[i][j + 1]->GetID() == EARTH && elements[i][j + 2]->GetID() == EARTH && elements[i + 1][j + 2]->GetID() == EARTH && elements[i - 1][j + 2]->GetID() == EARTH
                   && elements[i][j]->GetID() == SKY && elements[i + 1][j]->GetID() == SKY && elements[i - 1][j]->GetID() == SKY && elements[i + 1][j + 1]->GetID() == SKY && elements[i - 1][j + 1]->GetID() == SKY){
                       delete elements[i][j + 1];
                       elements[i][j + 1] = new TileAABB(SKY);
                   }
            }
        }*/

    }

    for(int i=nbrColumns - 1; i >= 0; --i){
        for(unsigned int j=nbrTilesPerColumn - 1; j >= 1; --j){
            if(static_cast<unsigned int>(i) > 1 && static_cast<unsigned int>(i) < nbrColumns - 2 && j > 1 && j < nbrTilesPerColumn - 3){
                if(GetTile(i, j)->GetID() == EARTH && GetTile(i + 1, j + 1)->GetID() == EARTH && GetTile(i - 1, j + 1)->GetID() == EARTH &&
                    GetTile(i, j + 2)->GetID() == EARTH && GetBelowTile(i, j)->GetID() == SKY){
                    ReplaceElementWith(i, j + 1, EARTH);
                }
            }
        }
    }



    for(unsigned int i=0; i<nbrColumns; ++i){
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            if(j > 1){
                if(GetAboveTile(i, j)->GetID() == SKY && GetTile(i, j)->GetID() == EARTH){
                        ReplaceElementWith(i, j, GRASS);
                }
            }
        }
    }
    for(unsigned int i=0; i<nbrColumns; ++i)
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            unsigned int nbr = rand() % 100;
            if(GetTile(i, j)->GetID() == SKY && j > 6 && nbr > 97)
                AddItem(APPLE, i, j);
        }

    /*for(unsigned int i=0; i<nbrColumns; ++i){
        for(unsigned int j=0; j<nbrTilesPerColumn; ++j){
            if(elements[i][j]->GetID() != SKY){
                if(i < nbrColumns - 1 && i > 0 && j < nbrTilesPerColumn - 1 && j > 0){
                    TileAABB* t = dynamic_cast<TileAABB*>(elements[i][j]);
                    if(GetAboveTile(i, j)->GetID() == SKY)
                        t->CS |= UP;
                    if(GetBelowTile(i, j)->GetID() == SKY)
                        t->CS |= DOWN;
                    if(GetLeftTile(i, j)->GetID() == SKY)
                        t->CS |= LEFT;
                    if(GetRightTile(i, j)->GetID() == SKY)
                        t->CS |= RIGHT;
                }
            }
            else
                t->CS = NONE;
        }
    }*/
}

void Map::RePlaceElements(sf::RenderWindow& W){
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            if(TileExists(i, j))
                elements[i][j]->AABB::SetPosition(i*TILES_SIZE, j*TILES_SIZE);
            /*else if(elements[i][j]->GetType() == type::SPRITE)
                elements[i][j]->SetPosition(i*32 - 1, j*32);*/
        }
    }
}

void Map::AddElement(unsigned int ID){
    if(elements.back().size() > 0)
        if(elements.back().back()->GetXPosition() + 33 > 1024 && elements.back().back()->GetYPosition() + 33 > 576)
            return;
    if(elements.back().size() + 1 > nbrTilesPerColumn)
        elements.push_back(std::vector<TileAABB*>());
    elements.back().push_back(tileList[ID]->Clone());
}

void Map::DeleteElement(unsigned int x, unsigned int y){
    if(TileExists(x, y)){
        delete elements[x][y];
        elements[x].erase(elements[x].begin() + y);
    }
}

void Map::ReplaceElementWith(unsigned int x, unsigned int y, unsigned int ID){
    if(TileExists(x, y)){
        int ax = elements[x][y]->Left();
        int ay = elements[x][y]->Up();
        delete elements[x][y];
        elements[x][y] = tileList[ID]->Clone();
        elements[x][y]->AABB::SetPosition(ax, ay);
    }
}

void Map::AddItem(unsigned int ID, int xPos, int yPos){
    //auto i = itemList[ID]->Clone();
    items.push_back(itemList[ID]->Clone());
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
        throw std::string("Can't access tile 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
    }

    catch(std::string& s){
        std::cerr << s << std::endl;
        return NULL;
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

TileAABB* Map::GetTile(int x, int y){
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

TileAABB* Map::GetAboveTile(int x, int y){
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

TileAABB* Map::GetLeftTile(int x, int y){
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

TileAABB* Map::GetRightTile(int x, int y){
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

TileAABB* Map::GetBelowTile(int x, int y){
    try{
        if(TileExists(x, y + 1))
            return elements[x][y + 1];
        throw std::string("Can't access tile right to 'elements[" + IntToString(x) + "][" + IntToString(y) + "]'.\nReturning NULL pointer, probably crashing.");
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
            TileAABB* t = dynamic_cast<TileAABB*>(elements[i][j]);
            if(t->Right() >= W.GetView().GetRect().Left && t->Left() <= W.GetView().GetRect().Right)
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
            if(elements[i][j]->GetID() != SKY){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if((GetAboveTile(i, j)->GetID() == SKY || GetBelowTile(i, j)->GetID() == SKY || GetRightTile(i, j)->GetID() == SKY || GetLeftTile(i, j)->GetID() == SKY)){
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
            if(dynamic_cast<TileAABB*>(elements[i][j])->GetID() != SKY){
                if(p.GetCollisionLimit()->WillCollision(*dynamic_cast<TileAABB*>(elements[i][j]))){
                    iCollisions.push_back(i);
                    jCollisions.push_back(j);
                }
            }
        }
    }
}*/

void Map::ComputeCollisions(){
    for(unsigned int i=0; i<elements.size(); ++i){
        for(unsigned int j=0; j<elements[i].size(); ++j){
            //if(elements[i][j]->Collides()){
                if(i >= 1 && i <= nbrColumns - 2){
                    if(j >= 1 && j <= nbrTilesPerColumn - 2){
                        if(!GetAboveTile(i, j)->Collides() || !GetBelowTile(i, j)->Collides() || !GetRightTile(i, j)->Collides() || !GetLeftTile(i, j)->Collides()){
                            elements[i][j]->SetCollide(true);
                        }
                        else
                            elements[i][j]->SetCollide(false);
                    }
                    else{
                        elements[i][j]->SetCollide(true);
                    }
                }
                else{
                    elements[i][j]->SetCollide(true);
                }
            //}
            if(elements[i][j]->GetID() == SKY)
                elements[i][j]->SetCollide(false);
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
}

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

