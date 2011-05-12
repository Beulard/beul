#include "AnimatedTile.hpp"

FrameList::FrameList(){

}

FrameList::FrameList(bool){
    frames.push_back(Frame(BA[LAVA], 1.f));
    frames.push_back(Frame(BA[LAVA + 1], 1.f));
}

Frame& FrameList::operator[](unsigned int index){
    try{
        if(index > frames.size() - 1)
            throw 0;
        else
            return frames[index];
    }
    catch(int){
        std::cerr << "Can't access FrameList[" << index << "], returning FrameList[0]." << std::endl;
        return frames[0];
    }
}

const unsigned int FrameList::size()   const{
    return frames.size();
}

FrameList frameList(1);


AnimationList::AnimationList(){

}

AnimationList::AnimationList(bool){
    std::vector<Frame*> f;
    f.push_back(new Frame(frameList[0]));
    f.push_back(new Frame(frameList[1]));
    anims.push_back(Animation(f));
}

Animation& AnimationList::operator[](unsigned int index){
    try{
        if(index > anims.size() - 1)
            throw 0;
        else
            return anims[index];
    }
    catch(int){
        std::cerr << "Can't access AnimationList[" << index << "], returning AnimationList[0]." << std::endl;
        return anims[0];
    }
}

const unsigned int AnimationList::size()   const{
    return anims.size();
}

AnimationList animationList(1);

AnimatedTile::AnimatedTile(){

}

AnimatedTile::~AnimatedTile(){

}

const Animation* AnimatedTile::GetAnim()    const{
    return anim;
}

void AnimatedTile::Draw(sf::RenderWindow& W){
    anim->SetPosition(left, up);
    anim->Animate(W.GetFrameTime());
    anim->Draw(W);
}

const unsigned int AnimatedTile::GetAnimationID()   const{
    return aid;
}

void AnimatedTile::onCollision(World& w){

}
/*const unsigned int AnimatedTile::GetNbrFrames() const{
    return nbrFrames;
}*/

/*void AnimatedTile::PushFrame(const Frame& f){
    anim->AddFrame(f);
}*/
