#pragma once

#include "Entity.h"
#include "EntityAttack.h"
#include "../Components/AllComponents.h"

class AnimationComp;

class Drillku : public Entity {
    private:
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
        bool isDigging = false;
        bool isAttacking = false;
        bool isDying = false;
        bool squashed = false;
    public:
        enum ALTER_LIFE {INCREASELIVES, DECREASELIVES, RESETLIVES};
        Drillku();
        Drillku(string name, string textureName);

        void setLives(ALTER_LIFE changeType);
        int getLives();
        void kill(int type);
        bool getIsDying();
        void setIsDying(bool value);
        void setIsSquashed(bool value);

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

        void setHairVisibility(bool value);
        bool getHairVisibility();
        void toggleIsDigging(bool newValue);
        bool getIsDigging();
        void toggleIsAttacking(bool newVaue);
        bool getIsAttacking();
        bool getIsSquashed();

        MovementComp* getMoveComp();
        AttackComp* getAtkComp();
        Sprite* getSprite();
        EntityAttack* getAttackSprite();
};