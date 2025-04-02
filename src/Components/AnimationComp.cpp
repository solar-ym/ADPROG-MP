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
            allSequences.push_back(AnimationSequence(4,4,"Attacking"));

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

    else if (owner->getName() == "Pookie") {
        allFrames.push_back((*res->getAtlas())["POOKIE_walk1"]); //0
        allFrames.push_back((*res->getAtlas())["POOKIE_walk2"]); 
            allSequences.push_back(AnimationSequence(0,1,"Walk"));
        allFrames.push_back((*res->getAtlas())["POOKIE_ghost1"]); // 2
        allFrames.push_back((*res->getAtlas())["POOKIE_ghost2"]); 
            allSequences.push_back(AnimationSequence(2,3,"Ghost"));
        allFrames.push_back((*res->getAtlas())["POOKIE_pop1"]); // 4
        allFrames.push_back((*res->getAtlas())["POOKIE_pop2"]); 
        allFrames.push_back((*res->getAtlas())["POOKIE_pop3"]); 
        allFrames.push_back((*res->getAtlas())["POOKIE_pop4"]); 
            allSequences.push_back(AnimationSequence(4,7,"Popping"));
            allSequences.back().setLooped(false);
        allFrames.push_back((*res->getAtlas())["POOKIE_squashed"]); // 8
            allSequences.push_back(AnimationSequence(8,8,"Squashed"));
            allSequences.back().setLooped(false);
    } 

    else if (owner->getName() == "Geygar") {
        allFrames.push_back((*res->getAtlas())["GEYGAR_walk1"]); //0
        allFrames.push_back((*res->getAtlas())["GEYGAR_walk2"]); 
            allSequences.push_back(AnimationSequence(0,1,"Walk"));
        allFrames.push_back((*res->getAtlas())["GEYGAR_ghost1"]); // 2
        allFrames.push_back((*res->getAtlas())["GEYGAR_ghost2"]); 
            allSequences.push_back(AnimationSequence(2,3,"Ghost"));
        allFrames.push_back((*res->getAtlas())["GEYGAR_pop1"]); // 4
        allFrames.push_back((*res->getAtlas())["GEYGAR_pop2"]); 
        allFrames.push_back((*res->getAtlas())["GEYGAR_pop3"]); 
        allFrames.push_back((*res->getAtlas())["GEYGAR_pop4"]); 
            allSequences.push_back(AnimationSequence(4,7,"Popping"));
            allSequences.back().setLooped(false);
        allFrames.push_back((*res->getAtlas())["GEYGAR_squashed"]); // 8
            allSequences.push_back(AnimationSequence(8,8,"Squashed"));
            allSequences.back().setLooped(false);
    } 
}

void AnimationComp :: animate() {
    if (internalTime < 50) internalTime++;

    
    if (owner->getName() == "Player") {
        Drillku* player = dynamic_cast<Drillku*>(owner);

        if (player->getIsAttacking()) {
            playSequence("Attacking");
            changeTexture(currentFrameIndex);
        } 
        else if (player->getMoveComp()->getIsMoving() && player->getIsDigging() && internalTime >= 10) {
            playSequence("Drill");
            changeTexture(currentFrameIndex);
        }  
        
        else if (player->getMoveComp()->getIsMoving() && internalTime >= 10) {
            playSequence("Walk");
            changeTexture(currentFrameIndex);
        } 

        else if (player->getIsDying() && internalTime >= 20) {
            playSequence("Defeat");
            changeTexture(currentFrameIndex);
        }

        else {
            changeTexture(currentFrameIndex);
        }
        player->getMoveComp()->fixInversion();
    }

    else if (owner->getName() == "Pookie") {
        Enemy* pookie = dynamic_cast<Enemy*>(owner);

        if (pookie->getIsDying() && internalTime >= 30) {
            playSequence("Popping");
            changeTexture(currentFrameIndex);
        }
    }

    else if (owner->getName() == "Geygar") {
        Enemy* geygar = dynamic_cast<Enemy*>(owner);

        if (geygar->getIsDying() && internalTime >= 30) {
            playSequence("Popping");
            changeTexture(currentFrameIndex);
        }
    }
}

void AnimationComp :: playSequence(string seqName) {
    AnimationSequence sequence;
    cout << "[ Anim Comp : Play Sequence start ] Index recieved: " << currentFrameIndex << endl;
    for (AnimationSequence seq: allSequences) {
        if (seq.getName() == seqName) {
            cout << "[ Anim Comp : Play Sequence search ] Name: " << seq.getName() << endl;
            sequence = seq;
            break;
        }
    }

    if (currentFrameIndex < sequence.start() || currentFrameIndex > sequence.end()) {
        currentFrameIndex = sequence.start();
    } else if (currentFrameIndex < sequence.end()){
        currentFrameIndex++;
    } else if (sequence.isLooped()) {
        currentFrameIndex = sequence.start();
    } else if (seqName == "Defeat" && currentFrameIndex == sequence.end()) {
        Drillku* player = dynamic_cast<Drillku*>(owner);
        player->setIsDying(false);
        currentFrameIndex = allSequences[WALK].start();
    } 

    else if (seqName == "Popping" && currentFrameIndex == sequence.end()) {
        Enemy* enemy = dynamic_cast<Enemy*>(owner);
        enemy->setIsDead(true);
    }

    cout << "[ Anim Comp : Play Sequence start ] Index changed to: " << currentFrameIndex << endl;
 
    internalTime = 0;
}

vector<IntRect> AnimationComp :: getAllFrames() {
    return allFrames;
}

void AnimationComp :: changeTexture(int index) {
    owner->getSprite()->setTextureRect(allFrames[index]);
}