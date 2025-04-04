#pragma once

#include "../Objects/EntityAttack.h"

/*
    Lets Drillku and Geygar attack.
*/

class AttackComp : public Component {
    private:
        enum ALTER_POS {INCREASE, DECREASE};
        EntityAttack* attackSprite;
        int pos = 140;

        bool shouldUnextend = false;
        bool shouldExtend = false;
        bool canExtend = true;

        int x = 0;
        int y = 0;

        float offset = TILE_SIZE/2;
        float offset2 = 4;
    public:
        AttackComp(string name, EntityAttack* attackSprite);
        void extend();
        void unextend();
        void reorient();

        void makePos(ALTER_POS alterType);

        void setUNExtendBool(bool newValue);
        void setExtendBool(bool newValue);
        bool getExtendBool(int type);
        void setCanExtend(bool newValue);
        bool getCanExtend();

        void setIsVisible(bool newValue);
        bool isVisible();

        int getAttX();
        int getAttY();

        EntityAttack* getAttackEntity();
};