#pragma once

#include "Entity.h"
#include "../Components/ColliderComp.h"

class Veggie : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
    public:
        Veggie() {}
        Veggie(string textureName) {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())[textureName];
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void setTileXY(int xV, int yV) {}
        int getTileX() { return x; }
        int getTileY() { return y; }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }
        ColliderComp* getColliderComp() { return nullptr; }

        Sprite* getSprite() {
            return entSprite;
        }
};