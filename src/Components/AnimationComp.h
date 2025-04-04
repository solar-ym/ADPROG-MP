#pragma once

#include "AnimationSequence.h"
#include "../Objects/Drillku.h"
#include "../Objects/enemies/Enemy.h"

/*
    This component is responsible for all of the animations,
*/

class AnimationComp : public Component {
    private:
        int internalTime = 0;
        int currentFrameIndex = 0;

        // allFrames contains all possible frames an entity has (all animations)
        vector<IntRect> allFrames;
        // an AnimationSequence contains information about a specific animation sequence or loop
        vector<AnimationSequence> allSequences;

        // enums for easier sequence handling for player
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