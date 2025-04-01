#include "Enemy.h"

Enemy :: Enemy () {}

Enemy :: Enemy(string name, string textureName) : Entity(name) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);

    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
}

void Enemy :: addComponent(Component* newComp) {
    comps.push_back(newComp);
}

// void 

// POSITION

void Enemy :: setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
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

ColliderComp* Enemy :: getColliderComp() {
    for(Component* cmp: comps)
        if(cmp->getName() == "ColliderComp") {
            ColliderComp* col = (ColliderComp*)cmp;
            return col;
        }
    return nullptr;
}