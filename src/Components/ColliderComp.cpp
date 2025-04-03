#include "ColliderComp.h"

ColliderComp::ColliderComp(float tileSize):
        Component("ColliderComp"){
    this->tileSize = tileSize;
}

float ColliderComp::getX(){
    if (owner->getName() == "Attack")
        return owner->getSprite()->getPosition().x;
    return owner->getSprite()->getPosition().x - tileSize/2;
}

float ColliderComp::getY(){
    if (owner->getName() == "Attack")
        return owner->getSprite()->getPosition().y;
    return owner->getSprite()->getPosition().y - tileSize/2;
}

float ColliderComp::getWidth(){
    if (owner->getName() == "Attack") {
        // if (owner->getSprite()->getRotation() == degrees(90))
        //     return owner->getSprite()->getTextureRect().size.x;
        // if (owner->getSprite()->getRotation() == degrees(-90))
        //     return -(owner->getSprite()->getTextureRect().size.x);
        if (owner->getSprite()->getRotation() == degrees(180)) // facing left
            return owner->getSprite()->getTextureRect().size.x;
    }
    return 50; 
}

float ColliderComp::getHeight(){
    // if (owner->getName() == "Attack") {
    //     if (owner->getSprite()->getRotation() == degrees(0))
    //         return owner->getSprite()->getTextureRect().size.y;
    //     if (owner->getSprite()->getRotation() == degrees(180))
    //         return -(owner->getSprite()->getTextureRect().size.y);
    // }
    return 50;
}