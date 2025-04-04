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
    this->stage = stage;
}


void Flower::setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x), TILE_SIZE*(y)});
}
int Flower::getTileX() { return x; }
int Flower::getTileY() { return y; }

void Flower::initialize() {}
void Flower::update() {}
void Flower::draw(RenderWindow *window) {
    window->draw(*entSprite);
}

void Flower::changeTexture(FlowerStage stage) {
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
    this->stage = stage;
}

ColliderComp* Flower::getColliderComp() { return nullptr; }

Sprite* Flower::getSprite() {
    return entSprite;
}

Flower::FlowerStage Flower::getFlowerStage(){ return stage; }