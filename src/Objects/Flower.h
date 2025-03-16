#pragma once

#include "Entity.h"

class Flower : public Entity {
    private:
        Sprite* entSprite;
    public:
        enum FlowerStage {BUD, MID, BLOOM};
        Flower() {}
        Flower(FlowerStage stage) {
            GD_GameResource* res = GD_GameResource::createInstance();
            
            IntRect rect;
            switch (stage) {
                case BUD:
                    rect = (*res->getAtlas())["FLOWER_bud"];
                    break;
                case MID:
                    rect = (*res->getAtlas())["FLOWER_mid"];
                    break;
                case BLOOM:
                    rect = (*res->getAtlas())["FLOWER_bloom"];
                    break;
            }
            
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }
};