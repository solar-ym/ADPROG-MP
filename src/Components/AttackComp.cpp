#include "AttackComp.h"

AttackComp :: AttackComp(string name, EntityAttack* attackSprite) 
    : Component("name") {  
        this->attackSprite = attackSprite;
}

void AttackComp :: extend() {
    if (attackSprite->getTextRect_X() < 150) {
        makePos(DECREASE);
        attackSprite->alterTextureRect(IntRect({pos,0}, {
            attackSprite->getTextRect_X() + 10,
            50
        }));
    } else {
        shouldExtend = false;
    }
}

void AttackComp :: unextend() {
    shouldExtend = false;
    if (attackSprite->getTextRect_X() > 10) {
        makePos(INCREASE);
        attackSprite->alterTextureRect(IntRect({pos,0}, 
            {attackSprite->getTextRect_X() - 10,
            50}));
    } else {
        shouldUnextend = false;
        attackSprite->toggleVisibility();
    }
}

void AttackComp :: reorient() {
    Vector2f ownerLoc = owner->getSprite()->getPosition();
    float offset = TILE_SIZE/2;
    
    MovementComp* moveComp = dynamic_cast<Drillku*>(owner)->getMoveComp();
    bool isFlipped = moveComp->checkFlipped();

    if (moveComp->isFacing() == MovementComp::UP) {
        attackSprite->setSpriteRotation(degrees(-90));
        if (!isFlipped)
            attackSprite->setSpritePosition(ownerLoc.x-offset, ownerLoc.y-offset);
        else 
        attackSprite->setSpritePosition(ownerLoc.x-4, ownerLoc.y-offset);

        x = owner->getTileX();
        y = owner->getTileY() - 1;
    }
    if (moveComp->isFacing() == MovementComp::DOWN) {
        attackSprite->setSpriteRotation(degrees(90));
        if (!isFlipped)
            attackSprite->setSpritePosition(ownerLoc.x+offset, ownerLoc.y+offset);
        else 
        attackSprite->setSpritePosition(ownerLoc.x+4, ownerLoc.y+offset);

        x = owner->getTileX();
        y = owner->getTileY() + 1;
    }
    if (moveComp->isFacing() == MovementComp::LEFT) {
        attackSprite->setSpriteRotation(degrees(180));
        attackSprite->setSpritePosition(ownerLoc.x-offset, ownerLoc.y+4); 

        x = owner->getTileX() - 1;
        y = owner->getTileY();
    }
    if (moveComp->isFacing() == MovementComp::RIGHT) {
        attackSprite->setSpriteRotation(degrees(0));
        attackSprite->setSpritePosition(ownerLoc.x+offset, ownerLoc.y-offset);

        x = owner->getTileX() + 1;
        y = owner->getTileY();
    }
}

void AttackComp :: makePos(ALTER_POS alterType) {
    switch (alterType) {
        case INCREASE:
            if (pos < 140) pos += 10;
            if (pos > 140) pos = 140;
            break;
        case DECREASE:
            if (pos > 0) pos -= 10;
            if (pos < 0) pos = 0;
            break;
    }
}

void AttackComp :: setUNExtendBool(bool newValue) {
    shouldUnextend = newValue;
}

void AttackComp :: setExtendBool(bool newValue) {
    shouldExtend = newValue;
}

bool AttackComp :: getExtendBool(int type) {
    if (type) return shouldUnextend;
    else return shouldExtend;
}

bool AttackComp :: isVisible() {
    return attackSprite->getVisibility();
}

int AttackComp :: getAttX() {
    return x;
}

int AttackComp :: getAttY() {
    return y;
}