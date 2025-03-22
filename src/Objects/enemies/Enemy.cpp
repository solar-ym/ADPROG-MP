#include "Enemy.h"

Enemy :: Enemy () {}

Enemy :: Enemy(string name, string textureName) : Entity(name) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);
}

void Enemy :: addComponent(Component* newComp) {
    comps.push_back(newComp);
}

// POSITION

void Enemy :: setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x), TILE_SIZE*(y)+(TILE_SIZE*3)});
}
int Enemy :: getTileX() {
    return x;
}
int Enemy :: getTileY() {
    return y;
}

void Enemy :: initialize() {}

void Enemy :: update() {}

void Enemy :: draw(RenderWindow *window) {
    window->draw(*entSprite);
}

Sprite* Enemy :: getSprite() {
    return entSprite;
}