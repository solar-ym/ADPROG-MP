#pragma once

#include "Entity.h"

class UIAsset : public GameObject {
    private:
        Sprite* entSprite;
        Texture tex;
    public:
        UIAsset() {}
        UIAsset(string textureName, Vector2f position) {
            GD_GameResource* res = GD_GameResource::createInstance();
            IntRect rect = (*res->getAtlas())[textureName];
            entSprite = new Sprite(*res->getTexture(),rect);
        }

        void initialize() {}
        void update() {}
        void draw(RenderWindow *window) {
            window->draw(*entSprite);
        }

        void changeTexture(string textureName) {
            if (tex.loadFromFile(textureName))
            entSprite->setTexture(tex);
        }

        // TEMPORARY
        void manualCreation(string textureName, float x, float y) {
            cout << "[UIAsset] attempting manualCreation()" << endl;
            if (tex.loadFromFile(textureName))
                entSprite = new Sprite(tex);
            cout << "[UIAsset] texture loaded" << endl;
            
            entSprite->move({x,y});
            cout << "[UIAsset] position set" << endl;
        }
};