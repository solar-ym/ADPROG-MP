#pragma once

#include "Component.h"

class AttackComp : public Component {
    private:
        enum ALTER_POS {INCREASE, DECREASE};
        Sprite* attackSprite;
        int pos = 140;

        bool shouldUnextend = false;
        bool shouldExtend = false;
    public:
        AttackComp(string name, Sprite* attackSprite);
        void extend();
        void unextend();
        void reorient(Sprite* owner);

        void makePos(ALTER_POS alterType);

        void setUNExtendBool(bool newValue);
        void setExtendBool(bool newValue);
        bool getExtendBool(int type);
};