#pragma once

#include "AnimationSequence.h"
#include "../Objects/Drillku.h"
#include "../Objects/Enemies/Enemy.h"

/*
    PLAYER SEQUENCES
        0: Walking
        1: Drilling
        2: Attacking
        3: Died from enemy
        4: Died from rock ver 1
        5: Died from rock ver 2
*/

class AnimationComp : public Component {
    private:
        int internalTime = 0;
        int currentFrameIndex = 0;
        vector<IntRect> allFrames;
        vector<AnimationSequence> allSequences;

        // enums for easier sequence handling
        enum PLAYER_SEQ {WALK, DRILL, ATTACK, DEATH, 
                            SQUASHED1, SQUASHED2};
    public:
        AnimationComp();
        AnimationComp(string compName);

        void attachComponent(Entity* owner);
        void loadFrames();

        void animate();
        void playSequence(string seqName);
        vector<IntRect> getAllFrames();

        void changeTexture(int index);
};