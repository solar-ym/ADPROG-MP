#pragma once

#include "Component.h"

class AttackComp : public Component {
    private:
        Sprite* attackSprite;
        int pos = 100;
    public:
        AttackComp(string name, Sprite* attackSprite);
        void extend();
        void unextend();
};