#pragma once

#include "Entity.h"

class Veggie : public Entity {
    private:
        Sprite* entSprite;
    public:
        Veggie() {}
        Veggie(string textureName) {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())[textureName];
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }
};