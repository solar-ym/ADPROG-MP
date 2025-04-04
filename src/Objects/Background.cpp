#include "Background.h"

Background::Background(){}

Background::Background(string textureName, int atlasNo) : Entity("Background") {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect;

    if(atlasNo == 1){
        rect = (*res->getUIAtlas1())[textureName];
        entSprite = new Sprite(*res->getUITexture1(),rect);
    } else if (atlasNo == 2) {
        rect = (*res->getUIAtlas2())[textureName];
        entSprite = new Sprite(*res->getUITexture2(),rect);
    }

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

Sprite* Background::getSprite() {
    return entSprite;
}
