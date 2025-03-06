#include "AttackComp.h"

AttackComp :: AttackComp(string name, Sprite* attackSprite) 
    : Component("name") {  
        this->attackSprite = attackSprite;
}

void AttackComp :: extend() {
    if (attackSprite->getTextureRect().size.x <= 125) {
        // pos -= 25;
        attackSprite->setTextureRect(IntRect({0,0}, 
            {attackSprite->getTextureRect().size.x+25,
            attackSprite->getTextureRect().size.y}));
    }
}

void AttackComp :: unextend() {
    if (attackSprite->getTextureRect().size.x >= 25) {
        // pos += 25;
        attackSprite->setTextureRect(IntRect({0,0}, 
            {attackSprite->getTextureRect().size.x-25,
            attackSprite->getTextureRect().size.y}));
    } else {
        attackSprite->setTextureRect(IntRect({100,0}, 
            {0,0}));
    }
}