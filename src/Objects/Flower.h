#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"

class Flower : public Entity {
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
        void changeTexture(FlowerStage stage);
        ColliderComp* getColliderComp();

        Sprite* getSprite();

        FlowerStage getFlowerStage();
    private:
        int x;
        int y;
        Sprite* entSprite;
        FlowerStage stage;
};