#include "AnimationComp.h"

AnimationComp :: AnimationComp() {}

AnimationComp :: AnimationComp(string compName) :
    Component(compName) {}

void AnimationComp :: attachComponent(Entity* owner) {
    Component::attachComponent(owner);
    loadFrames();
}

void AnimationComp :: loadFrames() {
    GD_GameResource* res = GD_GameResource::createInstance();

    /* 
        Pushes all possible frames into allFrames and registers the
        corresponding sequences (consecutive frames) to be played or looped.
    */
    if (owner->getName() == "Player") {
        allFrames.push_back((*res->getAtlas())["MIKU_walk1"]); // 0
        allFrames.push_back((*res->getAtlas())["MIKU_walk2"]);
            allSequences.push_back(AnimationSequence(0,1,"Walk"));

        allFrames.push_back((*res->getAtlas())["MIKU_drill1"]); // 2
        allFrames.push_back((*res->getAtlas())["MIKU_drill2"]);
            allSequences.push_back(AnimationSequence(2,3,"Drill"));

        allFrames.push_back((*res->getAtlas())["MIKU_attack"]); // 4
            allSequences.push_back(AnimationSequence(4,4,"Drill"));

        allFrames.push_back((*res->getAtlas())["MIKU_defeat1"]); // 5
        allFrames.push_back((*res->getAtlas())["MIKU_defeat2"]);
        allFrames.push_back((*res->getAtlas())["MIKU_defeat3"]);
        allFrames.push_back((*res->getAtlas())["MIKU_defeat4"]);
            allSequences.push_back(AnimationSequence(5,8,"Defeat"));
            allSequences.back().setLooped(false);

        allFrames.push_back((*res->getAtlas())["MIKU_squashNervous"]); // 9
        allFrames.push_back((*res->getAtlas())["MIKU_squashHorizontal"]);
            allSequences.push_back(AnimationSequence(9,10,"Squashed1"));
            allSequences.back().setLooped(false);

        allFrames.push_back((*res->getAtlas())["MIKU_squashNervous"]); //11
        allFrames.push_back((*res->getAtlas())["MIKU_squashVertical"]);
            allSequences.push_back(AnimationSequence(11,12,"Squashed2"));
            allSequences.back().setLooped(false);
    }
}

void AnimationComp :: animate() {
    if (internalTime < 20) internalTime++;

    
    if (owner->getName() == "Player") {
        Drillku* player = dynamic_cast<Drillku*>(owner);

        if (player->getIsAttacking()) {
            playSequence(ATTACK);
            changeTexture(currentFrameIndex);
        } 
        else if (player->getMoveComp()->getIsMoving() && player->getIsDigging() && internalTime >= 10) {
            playSequence(DRILL);
            changeTexture(currentFrameIndex);
        }  
        
        else if (player->getMoveComp()->getIsMoving() && internalTime >= 10) {
            playSequence(WALK);
            changeTexture(currentFrameIndex);
        } 

        else {
            changeTexture(currentFrameIndex);
        }
        player->getMoveComp()->fixInversion();
    }
}

void AnimationComp :: playSequence(int index) {
    if (currentFrameIndex < allSequences[index].start() || currentFrameIndex > allSequences[index].end()) {
        currentFrameIndex = allSequences[index].start();
    } else if (currentFrameIndex < allSequences[index].end()){
        currentFrameIndex++;
    } else if (allSequences[index].isLooped()) {
        currentFrameIndex = allSequences[index].start();
    }
    internalTime = 0;
}

vector<IntRect> AnimationComp :: getAllFrames() {
    return allFrames;
}

void AnimationComp :: changeTexture(int index) {
    owner->getSprite()->setTextureRect(allFrames[index]);
}