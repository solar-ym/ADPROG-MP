#include "UIAsset.h"

UIAsset::UIAsset() {}
UIAsset::UIAsset(string textureName, Vector2f position) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);
}

void UIAsset::initialize() {}
void UIAsset::update() {}
void UIAsset::draw(RenderWindow *window) {
    window->draw(*entSprite);
}

void UIAsset::changeTexture(string textureName) {
    if (tex.loadFromFile(textureName))
    entSprite->setTexture(tex);
}

// TEMPORARY
void UIAsset::manualCreation(string textureName, float x, float y) {
    if (tex.loadFromFile(textureName))
        entSprite = new Sprite(tex);
    
    entSprite->move({x,y});
}