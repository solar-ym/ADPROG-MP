#pragma once

#include "Entity.h"

class Background : public Entity {
    private:
        int x;
        int y;
        Sprite* entSprite;
        Texture tex;
    public:
        Background() {}
        Background(string textureName) : Entity("Background") {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())[textureName];
            entSprite = new Sprite(*res->getTexture(),rect);
            entSprite->setPosition({0,0});
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
        
        // TEMPORARY
        void manualCreation(string textureName) {
            if (tex.loadFromFile(textureName))
                entSprite = new Sprite(tex);
        }

        Sprite* getSprite() {
            return entSprite;
        }
};