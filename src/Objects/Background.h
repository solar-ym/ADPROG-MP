#pragma once

#include "Entity.h"

class Background : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
        Texture tex;
    public:
        Background();
        Background(string textureName, int atlasNo);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);
        ColliderComp* getColliderComp();
        
        Sprite* getSprite();
};