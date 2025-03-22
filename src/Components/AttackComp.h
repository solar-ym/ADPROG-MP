#pragma once

#include "MovementComp.h"
#include "../Objects/EntityAttack.h"

class AttackComp : public Component {
    private:
        enum ALTER_POS {INCREASE, DECREASE};
        EntityAttack* attackSprite;
        int pos = 140;

        bool shouldUnextend = false;
        bool shouldExtend = false;
    public:
        AttackComp(string name, EntityAttack* attackSprite);
        void extend();
        void unextend();
        void reorient();

        void makePos(ALTER_POS alterType);

        void setUNExtendBool(bool newValue);
        void setExtendBool(bool newValue);
        bool getExtendBool(int type);
};