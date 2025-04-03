#include "Veggie.h"

Veggie::Veggie() {}
Veggie::Veggie(string textureName) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);
}

void Veggie::setTileXY(int xV, int yV) {}
int Veggie::getTileX() { return x; }
int Veggie::getTileY() { return y; }

void Veggie::initialize() {}
void Veggie::update() {}
void Veggie::draw(RenderWindow *window) {
    window->draw(*entSprite);
}
ColliderComp* Veggie::getColliderComp() { return nullptr; }

Sprite* Veggie::getSprite() {
    return entSprite;
}