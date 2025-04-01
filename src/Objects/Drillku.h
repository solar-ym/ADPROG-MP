#pragma once

#include "Entity.h"
#include "EntityAttack.h"
#include "../Components/MovementComp.h"
#include "../Components/AttackComp.h"
#include "../Components/AnimationComp.h"
#include "../Components/ColliderComp.h"

class Drillku : public Entity {
    private:
        enum ALTER_LIFE {INCREASELIVES, DECREASELIVES, RESETLIVES};
        int livesLeft = 3;

        // tile coords
        int x = 0;
        int y = 0;

        // components
        MovementComp* movement;
        AttackComp* attack;
        AnimationComp* anim;
        ColliderComp* collision;

        // sprites
        EntityAttack* attackSprite;
        Sprite* entSprite;

        // animation
        int internalTime;

        bool isDigging = false;
        bool isAttacking = false;
        bool isDying = false;
    public:
        Drillku();
        Drillku(string name, string textureName);

        // void mikuMove(float x, float y);

        void setLives(ALTER_LIFE changeType);
        void kill();
        bool getIsDying();

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
        void toggleIsDigging(bool newValue);
        bool getIsDigging();
        void toggleIsAttacking(bool newVaue);
        bool getIsAttacking();

        MovementComp* getMoveComp();
        AttackComp* getAtkComp();
        ColliderComp* getColliderComp();
        Sprite* getSprite();
};