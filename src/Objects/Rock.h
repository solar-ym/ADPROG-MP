#pragma once

#include "Entity.h"

class Rock : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
    public:
        Rock() {}
        Rock() {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())["ROCK_default"];
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

        Sprite* getSprite() {
            return entSprite;
        }
};