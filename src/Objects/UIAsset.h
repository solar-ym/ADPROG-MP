#pragma once

#include "Entity.h"

class UIAsset : public GameObject {
    private:
        Sprite* entSprite;
        Texture tex;
    public:
        UIAsset();
        UIAsset(string textureName, Vector2f position);

        void initialize();
        void update();
        void draw(RenderWindow *window);

        void changeTexture(string textureName);
};