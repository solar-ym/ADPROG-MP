#include "AnimationSequence.h"

AnimationSequence :: AnimationSequence() {}
AnimationSequence :: AnimationSequence(int start, int end, string name) {
    startIndex = start;
    endIndex = end;
    this->name = name;
}
int AnimationSequence :: start() {
    return startIndex;
}
int AnimationSequence :: end() {
    return endIndex;
}
void AnimationSequence :: setLooped(bool value) {
    looped = value;    
}
bool AnimationSequence :: isLooped() {
    return looped;
}
string AnimationSequence :: getName() {
    return name;
}
