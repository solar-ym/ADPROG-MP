#pragma once

#include "Entity.h"

class Rock : public Entity {
    private:
        Sprite* entSprite;
    public:
        Rock() {}
        Rock() {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())["ROCK_default"];
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }
};