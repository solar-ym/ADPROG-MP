#pragma once

#include "../Utility/configurations.h"

class AnimationSequence {
    private:
        string name;
        int startIndex;
        int endIndex;
        bool looped = true;
    public:
        AnimationSequence();
        AnimationSequence(int start, int end, string name);
        int start();
        int end();
        void setLooped(bool value);
        bool isLooped();
        string getName();
};