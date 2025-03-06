#pragma once

#include "Entity.h"
#include "../Components/MovementComp.h"
#include "../Components/AttackComp.h"

class Drillku : public Entity {
    private:
        enum ALTER_LIFE {INCREASELIVES, DECREASELIVES, RESETLIVES};
        int livesLeft = 3;

        // components
        MovementComp* movement;
        AttackComp* attack;

        Sprite* attackSprite;
        Texture attTexture;

        Sprite* entSprite;
        Texture entTexture;
    public:
        Drillku();
        Drillku(string name);

        void mikuMove(float x, float y);

        void setLives(ALTER_LIFE changeType);
        void update(Keyboard::Scan keyCode);

        void draw(RenderWindow *window);

        
};