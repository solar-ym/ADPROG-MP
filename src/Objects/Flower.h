#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"

class Flower : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
    public:
        enum FlowerStage {BUD, MID, BLOOM};
        Flower();
        Flower(FlowerStage stage);

        void setTileXY(int xV, int yV);
        int getTileX();
        int getTileY();

        void initialize();
        void update();
        void draw(RenderWindow *window);
        ColliderComp* getColliderComp();

        Sprite* getSprite();
};