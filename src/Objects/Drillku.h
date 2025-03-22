#pragma once

#include "Entity.h"
#include "EntityAttack.h"
#include "../Components/MovementComp.h"
#include "../Components/AttackComp.h"

class Drillku : public Entity {
    private:
        enum ALTER_LIFE {INCREASELIVES, DECREASELIVES, RESETLIVES};
        int livesLeft = 3;

        int x = 0;
        int y = 0;

        // components
        MovementComp* movement;
        AttackComp* attack;

        EntityAttack* attackSprite;

        Sprite* entSprite;
    public:
        Drillku();
        Drillku(string name, string textureName);

        // void mikuMove(float x, float y);

        void setLives(ALTER_LIFE changeType);

        // attack-related
        void unextendHair();
        void extendHair();
        void setHairExtendBool(int type, bool newValue);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();
        
        void initialize();
        void update();
        void draw(RenderWindow *window);

        void toggleHairVisibility();
        bool getHairVisibility();

        MovementComp* getMoveComp();
        AttackComp* getAtkComp();
        Sprite* getSprite();
};