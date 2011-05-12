#include "Animation.hpp"

Animation::Animation(){
    currentFrame = 0;
}

Animation::Animation(const std::vector<Frame>& frames){
    for(unsigned int i=0; i<frames.size(); ++i){
        Frames.push_back(frames[i]);
    }
    currentFrame = 0;
}

Animation::Animation(const Animation& copy){
    for(unsigned int i=0; i<copy.Frames.size(); ++i){
        //Frames* f = new Frame(copy.Frames[i]);
        Frames.push_back(copy.Frames[i]);
        //delete f;
    }
    paused = copy.paused;
    totalTime = copy.totalTime;
    currentFrame = copy.currentFrame;
}

Animation::~Animation(){

}


void Animation::AddFrame(Frame& F){
    Frames.push_back(F);
}

const std::vector<Frame>& Animation::GetFrames()    const{
    return Frames;
}

const Frame& Animation::GetFrame(unsigned int index)    const{
    return Frames[index];
}

const unsigned int Animation::size()    const{
    return Frames.size();
}

void Animation::Draw(sf::RenderWindow& W){
    if(Frames.size() > 0)
        Frames[currentFrame].Draw(W);
}

void Animation::Animate(float time){
    if(!paused){
        totalTime += time;
        if(totalTime > Frames[currentFrame].GetFrameTime()){
            currentFrame++;
            totalTime = 0.f;
        }
        if(currentFrame > Frames.size() - 1)
            currentFrame = 0;
    }
}

void Animation::SetPosition(int x, int y){
    if(Frames.size() != 0){
        for(unsigned int i=0; i<Frames.size(); ++i){
            Frames[i].SetPosition(x, y);
        }
    }
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
