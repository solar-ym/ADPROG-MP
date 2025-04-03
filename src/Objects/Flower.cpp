#include "Flower.h"

Flower::Flower() {}
Flower::Flower(FlowerStage stage) {
    GD_GameResource* res = GD_GameResource::createInstance();
    
    IntRect rect;
    switch (stage) {
        case BUD:
            rect = (*res->getAtlas())["FLOWER_bud"];
            break;
        case MID:
            rect = (*res->getAtlas())["FLOWER_mid"];
            break;
        case BLOOM:
            rect = (*res->getAtlas())["FLOWER_bloom"];
            break;
    }
    
    entSprite = new Sprite(*res->getTexture(),rect);
}

void Flower::setTileXY(int xV, int yV) {}
int Flower::getTileX() { return x; }
int Flower::getTileY() { return y; }

void Flower::initialize() {}
void Flower::update() {}
void Flower::draw(RenderWindow *window) {
    window->draw(*entSprite);
}
ColliderComp* Flower::getColliderComp() { return nullptr; }

Sprite* Flower::getSprite() {
    return entSprite;
}
