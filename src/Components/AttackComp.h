#pragma once

#include "../Objects/EntityAttack.h"

class AttackComp : public Component {
    private:
        enum ALTER_POS {INCREASE, DECREASE};
        EntityAttack* attackSprite;
        int pos = 140;

        bool shouldUnextend = false;
        bool shouldExtend = false;

        int x = 0;
        int y = 0;
    public:
        AttackComp(string name, EntityAttack* attackSprite);
        void extend();
        void unextend();
        void reorient();

        void makePos(ALTER_POS alterType);

        void setUNExtendBool(bool newValue);
        void setExtendBool(bool newValue);
        bool getExtendBool(int type);

        void setIsVisible(bool newValue);
        bool isVisible();

        int getAttX();
        int getAttY();
};