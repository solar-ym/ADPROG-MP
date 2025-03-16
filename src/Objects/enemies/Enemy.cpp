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

void Enemy :: initialize() {}

void Enemy :: update() {}

void Enemy :: draw(RenderWindow *window) {
    window->draw(*entSprite);
}