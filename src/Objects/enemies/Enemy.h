#pragma once

#include "../Entity.h"
#include "../../Components/AllComponents.h"

class Enemy : public Entity {
    private:
        int x;
        int y;
        // components
        vector<Component*> comps;

        Sprite* entSprite;
        EntityAttack* attackSprite = nullptr;

        // animation
        bool isDying = false;
        bool isDead = false;
        bool squashed = false;
        bool isAttacking = false;
        bool ghostMode = false;
    public:
        Enemy();
        Enemy(string name, string textureName);

        void addComponent(Component* newComp);

        void kill();
        void squash();

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        Sprite* getSprite();
        AnimationComp* getAnimComp();
        MovementComp* getMoveComp();
        AttackComp* getAtkComp();
        EnemyBehaviorComp* behave();

        bool getIsDying();
        void setIsDying(bool value);
        bool getIsDead();
        void setIsDead(bool value);
        bool getIsSquashed();
        void setIsSquashed(bool value);

        bool getGhostMode();
        void setGhostMode(bool value);
        void setIsAttacking(bool value);
        bool getIsAttacking();
}; 