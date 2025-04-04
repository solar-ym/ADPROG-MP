#include "AttackComp.h"

/*
    EntityAttack is a class referring to the actual entity that the attack
    takes the form of.
*/
AttackComp :: AttackComp(string name, EntityAttack* attackSprite) 
    : Component(name) {  
        this->attackSprite = attackSprite;
}

// Increases the texture rect width while moving the sprite closer to the player, giving an extending effect.
void AttackComp :: extend() {
    if (attackSprite->getTextRect_X() < 150 && canExtend) {
        makePos(DECREASE);
        attackSprite->alterTextureRect(IntRect({pos,0}, {
            attackSprite->getTextRect_X() + 10,
            50
        }));
    } else {
        shouldExtend = false;
        if (owner->getName() == "Geygar") {
            shouldUnextend = true;
        }
    }
}

// Same as above but for unextending.
void AttackComp :: unextend() {
    shouldExtend = false;
    if (attackSprite->getTextRect_X() > 10) {
        makePos(INCREASE);
        attackSprite->alterTextureRect(IntRect({pos,0}, 
            {attackSprite->getTextRect_X() - 10,
            50}));
    } else {
        shouldUnextend = false;
        canExtend = true;
        attackSprite->setVisibility(false);
    }
}

// Fixes the attack sprite's location in relation to the player
void AttackComp :: reorient() {
    Vector2f ownerLoc = owner->getSprite()->getPosition();
    bool isPlayer = true;

    // since Drillku's attack sprite requires more manipulation to reorient than Geygar's, we keep track of the owner.
    if (owner->getName() != "Player") {
        offset2 = 25;
        isPlayer = false;
    }
    
    MovementComp* moveComp;
    if (owner->getName() == "Player")
        moveComp = dynamic_cast<Drillku*>(owner)->getMoveComp();
    else 
        moveComp = dynamic_cast<Enemy*>(owner)->getMoveComp();

    bool isFlipped = moveComp->checkFlipped();

    if (moveComp->isFacing() == MovementComp::UP) {
        attackSprite->setSpriteRotation(degrees(-90));
        if (!isPlayer)
            attackSprite->setSpritePosition(ownerLoc.x-offset2, ownerLoc.y-offset);
        else if (!isFlipped)
            attackSprite->setSpritePosition(ownerLoc.x-offset, ownerLoc.y-offset);
        else 
            attackSprite->setSpritePosition(ownerLoc.x-offset2, ownerLoc.y-offset);

        x = owner->getTileX();
        y = owner->getTileY() - 1;
    }
    if (moveComp->isFacing() == MovementComp::DOWN) {
        attackSprite->setSpriteRotation(degrees(90));
        if (!isPlayer)
            attackSprite->setSpritePosition(ownerLoc.x+offset2, ownerLoc.y+offset);
        else if (!isFlipped)
            attackSprite->setSpritePosition(ownerLoc.x+offset, ownerLoc.y+offset);
        else
            attackSprite->setSpritePosition(ownerLoc.x+offset2, ownerLoc.y+offset);

        x = owner->getTileX();
        y = owner->getTileY() + 1;
    }
    if (moveComp->isFacing() == MovementComp::LEFT) {
        attackSprite->setSpriteRotation(degrees(180));
        if (!isPlayer)
            attackSprite->setSpritePosition(ownerLoc.x-offset, ownerLoc.y+offset2);
        else
            attackSprite->setSpritePosition(ownerLoc.x-offset, ownerLoc.y+offset2); 

        x = owner->getTileX() - 1;
        y = owner->getTileY();
    }
    if (moveComp->isFacing() == MovementComp::RIGHT) {
        attackSprite->setSpriteRotation(degrees(0));
        if (!isPlayer)
            attackSprite->setSpritePosition(ownerLoc.x+offset, ownerLoc.y-offset2);
        else
            attackSprite->setSpritePosition(ownerLoc.x+offset, ownerLoc.y-offset);

        x = owner->getTileX() + 1;
        y = owner->getTileY();
    }
}

/*
    Used in extend() and unextend() to alter where in the texture image 
    (the actual .png) the IntRect starts taking from. This is what 
    causes the actual extending/shooting out effect.
*/
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

// Utility Functions below

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

void AttackComp :: setCanExtend(bool newValue) {
    canExtend = newValue;
}

bool AttackComp :: getCanExtend() {
    return canExtend;
}

void AttackComp :: setIsVisible(bool newValue) {
    attackSprite->setVisibility(newValue);
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

EntityAttack* AttackComp :: getAttackEntity() {
    return attackSprite;
}