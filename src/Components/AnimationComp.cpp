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

        allFrames.push_back((*res->getAtlas())["GEYGAR_attack"]); // 9
            allSequences.push_back(AnimationSequence(9,9,"Attacking"));
            allSequences.back().setLooped(false);
    } 
}

/*
    Will animate change the animation sequence being played based on
    the [ owner ]'s information and state.
*/
void AnimationComp :: animate() {
    if (internalTime < 50) internalTime++;

    
    if (owner->getName() == "Player") {
        Drillku* player = dynamic_cast<Drillku*>(owner);

        if (player->getIsDying() && internalTime >= 20) {
            playSequence("Defeat");
            changeTexture(currentFrameIndex);
        }

        else if (player->getIsSquashed() && internalTime >= 20) {
            if (player->getMoveComp()->isFacing() == MovementComp::LEFT || player->getMoveComp()->isFacing() == MovementComp::RIGHT)
                playSequence("Squashed1");
            else
                playSequence("Squashed2");
            changeTexture(currentFrameIndex);
        } 

        else if (player->getIsAttacking()) {
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

        else if (pookie->getIsSquashed()) {
            playSequence("Squashed");
            changeTexture(currentFrameIndex);
        } 

        else if (pookie->getMoveComp()->getIsMoving() && pookie->getGhostMode() && internalTime >= 10) {
            playSequence("Ghost");
            changeTexture(currentFrameIndex);
        }

        else if (pookie->getMoveComp()->getIsMoving() && internalTime >= 10) {
            playSequence("Walk");
            changeTexture(currentFrameIndex);
        } 
        
        else {
            changeTexture(currentFrameIndex);
        }
        pookie->getMoveComp()->fixInversion();
    }

    else if (owner->getName() == "Geygar") {
        Enemy* geygar = dynamic_cast<Enemy*>(owner);

        if (geygar->getIsDying() && internalTime >= 30) {
            playSequence("Popping");
            changeTexture(currentFrameIndex);
        }  

        else if (geygar->getIsSquashed()) {
            playSequence("Squashed");
            changeTexture(currentFrameIndex);
        } 

        else if (geygar->getIsAttacking()) {
            playSequence("Attacking");
            changeTexture(currentFrameIndex);
        } 

        else if (geygar->getMoveComp()->getIsMoving() && geygar->getGhostMode() && internalTime >= 10) {
            playSequence("Ghost");
            changeTexture(currentFrameIndex);
        }

        else if (geygar->getMoveComp()->getIsMoving() && internalTime >= 10) {
            playSequence("Walk");
            changeTexture(currentFrameIndex);
        } 

        else {
            changeTexture(currentFrameIndex);
        }
        geygar->getMoveComp()->fixInversion();
    }
}

/*
    Will play a specific sequence from the allSequences vector based on what was
    called in animate()
*/
void AnimationComp :: playSequence(string seqName) {
    AnimationSequence sequence;
    for (AnimationSequence seq: allSequences) {
        if (seq.getName() == seqName) {
            sequence = seq;
            break;
        }
    }

    if ((seqName == "Popping" || seqName == "Squashed") && currentFrameIndex == sequence.end()) {
        Enemy* enemy = dynamic_cast<Enemy*>(owner);
        enemy->setIsDead(true);
    }

    else if (currentFrameIndex < sequence.start() || currentFrameIndex > sequence.end()) {
        currentFrameIndex = sequence.start();
    } else if (currentFrameIndex < sequence.end()){
        currentFrameIndex++;
    } else if (sequence.isLooped()) {
        currentFrameIndex = sequence.start();
    } else if ((seqName == "Defeat" || seqName == "Squashed1" || seqName == "Squashed2")
               && currentFrameIndex == sequence.end()) {
        Drillku* player = dynamic_cast<Drillku*>(owner);
        player->setIsDying(false);
        player->setIsSquashed(false);
        currentFrameIndex = allSequences[WALK].start();
    } 
 
    internalTime = 0;
}

vector<IntRect> AnimationComp :: getAllFrames() {
    return allFrames;
}

/*
    Updates the texture rect based on the recieved index. Takes
    from the vector of IntRects saved in [ allFrames ]
*/
void AnimationComp :: changeTexture(int index) {
    owner->getSprite()->setTextureRect(allFrames[index]);
}