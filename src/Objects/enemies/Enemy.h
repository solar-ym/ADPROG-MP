#pragma once

#include "../Entity.h"
#include "../../Components/AllComponents.h"

// class AnimationComp;

class Enemy : public Entity {
    private:
        int x;
        int y;
        // components
        vector<Component*> comps;

        Sprite* entSprite;

        // animation
        bool isDying = false;
        bool isDead = false;
    public:
        Enemy();
        Enemy(string name, string textureName);

        void addComponent(Component* newComp);

        void kill();

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);

        Sprite* getSprite();
        ColliderComp* getColliderComp();
        AnimationComp* getAnimComp();
        MovementComp* getMoveComp();
        // Component* getComp(int type);

        bool getIsDying();
        void setIsDying(bool value);
        bool getIsDead();
        void setIsDead(bool value);
}; 