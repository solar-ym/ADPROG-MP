#pragma once

#include "Entity.h"

class Background : public Entity {
    private:
        Sprite* entSprite;
        Texture tex;
    public:
        Background() {}
        Background(string textureName) {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())[textureName];
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }
        
        // TEMPORARY
        void manualCreation(string textureName) {
            if (tex.loadFromFile(textureName))
                entSprite = new Sprite(tex);
        }
};