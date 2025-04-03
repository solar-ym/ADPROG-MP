#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"

class Veggie : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
    public:
        Veggie();
        Veggie(string textureName);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);
        ColliderComp* getColliderComp();

        Sprite* getSprite();
};