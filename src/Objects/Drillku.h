#pragma once

#include "Entity.h"
#include "EntityAttack.h"
#include "../Components/MovementComp.h"
#include "../Components/AttackComp.h"

class Drillku : public Entity {
    private:
        enum ALTER_LIFE {INCREASELIVES, DECREASELIVES, RESETLIVES};
        int livesLeft = 3;

        // components
        MovementComp* movement;
        AttackComp* attack;

        EntityAttack* attackSprite;

        Sprite* entSprite;
    public:
        Drillku();
        Drillku(string name, string textureName);

        void mikuMove(float x, float y);

        void setLives(ALTER_LIFE changeType);

        // attack-related
        void unextendHair();
        void extendHair();
        void setHairExtendBool(int type, bool newValue);
        
        void initialize();
        void update();
        void draw(RenderWindow *window);

        MovementComp* getMoveComp();
        Sprite* getEntSprite();
};