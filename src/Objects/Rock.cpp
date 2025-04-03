#include "Rock.h"

Rock::Rock() {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())["ROCK_default"];
    entSprite = new Sprite(*res->getTexture(),rect);
}

void Rock::setTileXY(int xV, int yV) {}
int Rock::getTileX() { return x; }
int Rock::getTileY() { return y; }

void Rock::initialize() {}
void Rock::update() {}
void Rock::draw(RenderWindow *window) {
    window->draw(*entSprite);
}

ColliderComp* Rock::getColliderComp() { return nullptr; }

Sprite* Rock::getSprite() {
    return entSprite;
}
