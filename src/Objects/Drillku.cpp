#include "Drillku.h"

Drillku :: Drillku() {}

Drillku :: Drillku (string name, string textureName) : Entity(name) {
    GD_GameResource* res = GD_GameResource::createInstance();
    IntRect rect = (*res->getAtlas())[textureName];
    entSprite = new Sprite(*res->getTexture(),rect);

    entSprite->setOrigin({rect.size.x/2.f, rect.size.y/2.f});
    setTileXY(6,5);

    attackSprite = new EntityAttack(this, "ATTACK_drillku.png");
    attackSprite->alterTextureRect(IntRect({140, 0}, {10,50})); 

    movement = new MovementComp("MovementComp", movement->PLAYER, entSprite);
    attack = new AttackComp("AttackComp", attackSprite);
    anim = new AnimationComp("AnimationComp");
    collision = new ColliderComp(TILE_SIZE);

    movement->attachComponent(this);
    attack->attachComponent(this);
    anim->attachComponent(this);
    collision->attachComponent(this);
}

// GAME RELATED

void Drillku :: setLives(ALTER_LIFE changeType) {
    switch (changeType) {
        case INCREASELIVES: livesLeft++;
            break;
        case DECREASELIVES: livesLeft--;
            break;
        case RESETLIVES: livesLeft = 3;
    }
}

void Drillku :: kill() {
    isDying = true;
    isDigging = false;
    isAttacking = false;
    movement->setMovingBool(false);
    attack->setExtendBool(false);
    attack->setUNExtendBool(false);
    attack->setIsVisible(false);
    if (movement->checkFlipped()) movement->invertTexture();
    entSprite->setRotation(degrees(0));
    attack->reorient();
}

bool Drillku :: getIsDying() {
    return isDying;
}

void Drillku :: setIsDying(bool value) {
    isDying = value;
}

// ATTACK-RELATED

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
    x = (entSprite->getPosition().x / TILE_SIZE);
    return x;
}
int Drillku :: getTileY() {
    y = (entSprite->getPosition().y / TILE_SIZE) - SKY_HEIGHT;
    return y;
}

// GENERAL

void Drillku :: initialize() {}

void Drillku :: update() {
    extendHair();
    unextendHair();

    if (!isDying) movement->move();
    anim->animate();
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

ColliderComp* Drillku :: getColliderComp() {
    return collision;
}

Sprite* Drillku :: getSprite() {
    return entSprite;
}

void Drillku :: setHairVisibility(bool value) {
    attackSprite->setVisibility(value);
}

bool Drillku :: getIsDigging() {
    return isDigging;
}

void Drillku :: toggleIsAttacking(bool newVaue) {
    isAttacking = newVaue;
}

bool Drillku :: getIsAttacking() {
    return isAttacking;
}

bool Drillku :: getHairVisibility() {
    return attackSprite->getVisibility();
}

void Drillku :: toggleIsDigging(bool newValue) {
    isDigging = newValue;
}

EntityAttack* Drillku :: getAttackSprite() {
    return attackSprite;
}