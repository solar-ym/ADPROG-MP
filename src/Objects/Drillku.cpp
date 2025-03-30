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

    allFrames.push_back((*res->getAtlas())["MIKU_walk1"]); // 0
    allFrames.push_back((*res->getAtlas())["MIKU_walk2"]);
    allFrames.push_back((*res->getAtlas())["MIKU_drill1"]); // 2
    allFrames.push_back((*res->getAtlas())["MIKU_drill2"]);
    allFrames.push_back((*res->getAtlas())["MIKU_attack"]); // 4
    allFrames.push_back((*res->getAtlas())["MIKU_defeat1"]); // 5
    allFrames.push_back((*res->getAtlas())["MIKU_defeat2"]);
    allFrames.push_back((*res->getAtlas())["MIKU_defeat3"]);
    allFrames.push_back((*res->getAtlas())["MIKU_defeat4"]);
    allFrames.push_back((*res->getAtlas())["MIKU_squashNervous"]); // 9
    allFrames.push_back((*res->getAtlas())["MIKU_squashHorizontal"]);
    allFrames.push_back((*res->getAtlas())["MIKU_squashVertical"]);
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

void Drillku :: changeTexture(int index) {
    entSprite->setTextureRect(allFrames[index]);
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
    return x;
}
int Drillku :: getTileY() {
    return y;
}

// GENERAL

void Drillku :: initialize() {}

void Drillku :: update() {
    if (internalTime < 100) internalTime++;

    x = (entSprite->getPosition().x / TILE_SIZE);
    y = (entSprite->getPosition().y / TILE_SIZE) - SKY_HEIGHT;

    extendHair();
    unextendHair();

    movement->move();

    if (isDigging && internalTime >= 10) {
        animateDrill();
        internalTime = 0;
    } else 
    
    if (movement->getIsMoving() && internalTime >= 10) {
        animateWalk();
        internalTime = 0;
    } 
}

void Drillku :: draw(RenderWindow *window) {
    window->draw(*entSprite);
    if (attackSprite->getVisibility())
        attackSprite->draw(window);
}

void Drillku :: animateWalk() {
    if (currentFrameIndex == 0) {
        changeTexture(1);
        currentFrameIndex = 1;
    }
    else if (currentFrameIndex == 1) {
        changeTexture(0);
        currentFrameIndex = 0;
    }
    if (movement->checkFlipped()) 
        movement->fixInversion();
}

void Drillku :: animateDrill() {
    if (currentFrameIndex == 2) {
        changeTexture(3);
        currentFrameIndex = 3;
    }
    else if (currentFrameIndex == 3) {
        changeTexture(2);
        currentFrameIndex = 2;
    }
    if (movement->checkFlipped()) 
        movement->fixInversion();
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

void Drillku :: toggleIsDigging(bool newValue) {
    isDigging = newValue;
    if (isDigging && currentFrameIndex != 3 && currentFrameIndex != 2) currentFrameIndex = 2;
    else currentFrameIndex = 0;
}