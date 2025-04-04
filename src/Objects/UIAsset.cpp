#include "UIAsset.h"

UIAsset::UIAsset() {}
UIAsset::UIAsset(string textureName, Vector2f position) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getUIAtlas1())[textureName];
    entSprite = new Sprite(*res->getUITexture1(),rect);

    entSprite->setPosition(position);
}

void UIAsset::initialize() {}
void UIAsset::update() {}
void UIAsset::draw(RenderWindow *window) {
    window->draw(*entSprite);
}

void UIAsset::changeTexture(string textureName) {
    GD_GameResource* res = GD_GameResource::createInstance();

    IntRect rect = (*res->getUIAtlas1())[textureName];
    entSprite->setTextureRect(rect);
}