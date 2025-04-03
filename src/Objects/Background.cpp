#include "Background.h"

Background::Background(){}

Background::Background(string textureName) : Entity("Background") {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);
    entSprite->setPosition({0,0});
}

void Background::setTileXY(int xV, int yV) {}

int Background::getTileX() { return x; }

int Background::getTileY() { return y; }

void Background::initialize() {}

void Background::update() {}

void Background::draw(RenderWindow *window) {
    window->draw(*entSprite);
}

ColliderComp* Background::getColliderComp() { return nullptr; }
        
// TEMPORARY
void Background::manualCreation(string textureName) {
    if (tex.loadFromFile(textureName))
        entSprite = new Sprite(tex);
}

Sprite* Background::getSprite() {
    return entSprite;
}
