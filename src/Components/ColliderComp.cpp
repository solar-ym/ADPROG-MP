#include "ColliderComp.h"

ColliderComp::ColliderComp(float tileSize):
        Component("ColliderComp"){
    this->tileSize = tileSize;
}

float ColliderComp::getX(){
    // cout << "getX: " << owner->getSprite()->getPosition().x << endl;
    if (owner->getName() == "Attack")
        return owner->getSprite()->getPosition().x; // but for the attack sprite its top left
    return owner->getSprite()->getPosition().x - tileSize/2; // i cannot change the attack sprite origin i thinkj
}

float ColliderComp::getY(){
    // cout << "getY" << endl;
    if (owner->getName() == "Attack")
        return owner->getSprite()->getPosition().y;
    return owner->getSprite()->getPosition().y - tileSize/2;
}
// 
float ColliderComp::getWidth(){
    // cout << "getW" << endl;
    // cout << "text rect x: " << owner->getSprite()->getTextureRect().size.x << endl;
    if (owner->getName() == "Attack") {
        // if (owner->getSprite()->getRotation() == degrees(90))
        //     return owner->getSprite()->getTextureRect().size.x;
        // if (owner->getSprite()->getRotation() == degrees(-90))
        //     return -(owner->getSprite()->getTextureRect().size.x);
        if (owner->getSprite()->getRotation() == degrees(180)) // facing left
            return owner->getSprite()->getTextureRect().size.x; // i will show u the issue withthsui
    }
    return 50; 
}

float ColliderComp::getHeight(){
    // cout << "getH" << endl;
    // cout << "text rect y: " << owner->getSprite()->getTextureRect().size.y << endl;
    // if (owner->getName() == "Attack") {
    //     if (owner->getSprite()->getRotation() == degrees(0))
    //         return owner->getSprite()->getTextureRect().size.y;
    //     if (owner->getSprite()->getRotation() == degrees(180))
    //         return -(owner->getSprite()->getTextureRect().size.y);
    // }
    return 50;
}