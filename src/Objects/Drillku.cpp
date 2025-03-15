#include "Drillku.h"

Drillku :: Drillku() {}

Drillku :: Drillku (string name, string textureName) : Entity(name) {
    
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);

    attackSprite = new EntityAttack(entSprite, "ATTACK_drillku.png");
    attackSprite->alterTextureRect(IntRect({140, 0}, {10,50})); 

    movement = new MovementComp("MovementComp", movement->PLAYER, entSprite);
    attack = new AttackComp("AttackComp", attackSprite);

    movement->attachComponent(this);
    attack->attachComponent(this);
}

void Drillku :: mikuMove(float x, float y) {
    entSprite->move({x,y});
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

// GENERAL

void Drillku :: initialize() {
    
}

void Drillku :: update() {
    attackSprite->setSpritePosition(entSprite);
    attack->reorient(entSprite);
    extendHair();
    unextendHair();
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

Sprite* Drillku :: getEntSprite() {
    return entSprite;
}