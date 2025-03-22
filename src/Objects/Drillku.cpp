#include "Drillku.h"

Drillku :: Drillku() {}

Drillku :: Drillku (string name, string textureName) : Entity(name) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);

    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    setTileXY(6,6);

    attackSprite = new EntityAttack(this, "ATTACK_drillku.png");
    attackSprite->alterTextureRect(IntRect({140, 0}, {10,50})); 

    movement = new MovementComp("MovementComp", movement->PLAYER, entSprite);
    attack = new AttackComp("AttackComp", attackSprite);

    movement->attachComponent(this);
    attack->attachComponent(this);
}

void Drillku :: setLives(ALTER_LIFE changeType) {
    switch (changeType) {
        case INCREASELIVES: livesLeft++;
            break;
        case DECREASELIVES: livesLeft--;
            break;
        case RESETLIVES: livesLeft = 3;
    }
}

void Drillku :: unextendHair() {
    if (attack->getExtendBool(1)) attack->unextend();
}

void Drillku :: extendHair() {
    if (attack->getExtendBool(0)) attack->extend();
}

void Drillku :: setHairExtendBool(int type, bool newValue) {
    if (type) attack->setUNExtendBool(newValue);
    else attack->setExtendBool(newValue);
}

// POSITION

void Drillku :: setTileXY(int xV, int yV) {
    x = xV; y = yV;
    entSprite->setPosition({TILE_SIZE*(x+0.5f), TILE_SIZE*(y+0.5f)+(TILE_SIZE*SKY_HEIGHT)});
}
int Drillku :: getTileX() {
    return x;
}
int Drillku :: getTileY() {
    return y;
}

// GENERAL

void Drillku :: initialize() {
    
}

void Drillku :: update() {
    extendHair();
    unextendHair();
    movement->move();
}

void Drillku :: draw(RenderWindow *window) {
    window->draw(*entSprite);
    if (attackSprite->getVisibility())
        attackSprite->draw(window);
}

// GETTERS

MovementComp* Drillku :: getMoveComp() {
    return movement;
}

AttackComp* Drillku :: getAtkComp() {
    return attack;
}

Sprite* Drillku :: getSprite() {
    return entSprite;
}

void Drillku :: toggleHairVisibility() {
    attackSprite->toggleVisibility();
}

bool Drillku :: getHairVisibility() {
    return attackSprite->getVisibility();
}