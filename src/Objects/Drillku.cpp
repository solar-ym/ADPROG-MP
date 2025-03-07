#include "Drillku.h"

Drillku :: Drillku() {}

Drillku :: Drillku (string name) : 
            Entity(name) {

    if (entTexture.loadFromFile("../../sprites/MIKU_attack.png"))
        entSprite = new Sprite(entTexture);

    if (attTexture.loadFromFile("../../sprites/ATTACK_drillku.png"))
        attackSprite = new Sprite(attTexture);
    attackSprite->setPosition({entSprite->getPosition().x+50, entSprite->getPosition().y});
    attackSprite->setTextureRect(IntRect({140, 0}, {10,50})); 

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

void Drillku :: update() {
    attackSprite->setPosition({entSprite->getPosition().x+50, entSprite->getPosition().y});
    attack->reorient(entSprite);
    extendHair();
    unextendHair();
}

void Drillku :: draw(RenderWindow *window) {
    window->draw(*entSprite);
    window->draw(*attackSprite);
}

// GETTERS

MovementComp* Drillku :: getMoveComp() {
    return movement;
}

Sprite* Drillku :: getEntSprite() {
    return entSprite;
}