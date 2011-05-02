#include "Animation.hpp"

Animation::Animation(){
    currentFrame = 0;
}

Animation::~Animation(){
    for(unsigned int i=0; i<Frames.size(); ++i)
        delete Frames[i];
}


void Animation::AddFrame(const Frame& F){
    Frames.push_back(new Frame(F));
}

const Frame* Animation::GetFrame(unsigned int index)    const{
    return Frames[index];
}

void Animation::Draw(sf::RenderWindow& W){
    if(Frames.size() > 0)
        Frames[currentFrame]->Draw(W);
}

void Animation::Animate(float time){
    if(!paused){
        totalTime += time;
        if(totalTime > Frames[currentFrame]->GetFrameTime()){
            currentFrame++;
            totalTime = 0.f;
        }
        if(currentFrame > Frames.size() - 1)
            currentFrame = 0;
    }
}

void Animation::SetPosition(int x, int y){
    for(unsigned int i=0; i<Frames.size(); ++i)
        Frames[i]->SetPosition(x, y);
}

void Animation::Play(){
    paused = false;
}

void Animation::Pause(){
    paused = true;
}

void Animation::Stop(){
    paused = true;
    currentFrame = 0;
}

void Animation::Reset(){
    paused = false;
    currentFrame = 0;
}
