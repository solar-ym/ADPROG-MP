#pragma once

#include "../Utility/configurations.h"

class AnimationSequence {
    private:
        string name;
        int startIndex;
        int endIndex;
        bool looped = true;
    public:
        AnimationSequence(int start, int end, string name) {
            startIndex = start;
            endIndex = end;
            this->name = name;
        }
        int start() {
            return startIndex;
        }
        int end() {
            return endIndex;
        }
        void setLooped(bool value) {
            looped = value;    
        }
        bool isLooped() {
            return looped;
        }
};