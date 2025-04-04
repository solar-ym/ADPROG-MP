#pragma once

#include "Entity.h"

class EntityAttack : public Entity {
    private:
        int x;
        int y;

        ColliderComp* collision;
        
        Sprite* attackSprite;
        Texture attTexture;
        bool isVisible = false;
    public:
        EntityAttack();
        EntityAttack(Entity* owner, string textureName);

        void setVisibility(bool value);
        bool getVisibility();
        void alterTextureRect(IntRect newRect);
        void setSpriteRotation(Angle newRotation);
        void setSpritePosition(float x, float y);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);
        ColliderComp* getColliderComp();

        Sprite* getSprite();

        int getTextRect_X();
        int getTextRect_Y();
};