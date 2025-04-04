#include "Veggie.h"

Veggie::Veggie() {}
Veggie::Veggie(string textureName) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);
}

void Veggie::setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x), TILE_SIZE*(y)+(TILE_SIZE*SKY_HEIGHT)});
}
int Veggie::getTileX() { return x; }
int Veggie::getTileY() { return y; }

void Veggie::initialize() {}
void Veggie::update() {}
void Veggie::draw(RenderWindow *window) {
    //Only draws if it appears on the screen
    if(isEnabled)
        window->draw(*entSprite);
}

void Veggie::setEnabled(bool enable){
    isEnabled = enable;
}

void Veggie::setTimer(int newTime){
    timer = newTime;
}

bool Veggie::getEnabled(){ return isEnabled; }

int Veggie::getTimer() { return timer; }

Sprite* Veggie::getSprite() {
    return entSprite;
}