#include "Item.hpp"



/*******    ITEMLIST    ********/

ItemList itemList;

void ItemList::RegisterItem(Item* i){
    items.push_back(i);
}

Item* ItemList::operator[](unsigned int index){
    try{
        if(index > items.size() - 1)
            throw 0;
        else
            return items[index]->Clone();
    }
    catch(int){
        std::cerr << "Cant access ItemList[" << index << "], returning ItemList[0]." << std::endl;
        return items[0]->Clone();
    }
}

const unsigned int ItemList::size() const{
    return items.size();
}


/*******    APPEARANCES    *********/

ItemAppearances::ItemAppearances(bool){
    push_back(I.appleimg);
    push_back(I.rocketlauncherimg);
    push_back(I.rocketlauncherimg);
}

ItemAppearances IA(1);

Item::Item(){
    id = ROCKETLAUNCHER;
    appearance = &IA[id];
}

Item::~Item(){

}

const unsigned int Item::GetID()    const{
    return id;
}

void Item::Draw(sf::RenderWindow& W){
    appearance->SetPosition(left, up);
    W.Draw(*appearance);
}

void Item::SetPosition(float x, float y){
    AABB::SetPosition(x, y);
    appearance->SetPosition(x, y);
}

/*void Item::onGet(World& w){

}

void Item::onUse(World& w){

}*/
