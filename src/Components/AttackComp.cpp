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
    }
}

void AttackComp :: reorient(Sprite* owner) {
    //fix rotation here
    attackSprite->setSpriteRotation(owner->getRotation());
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