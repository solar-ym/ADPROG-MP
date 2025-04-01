#include "ColliderComp.h"

ColliderComp::ColliderComp(float tileSize):
        Component("ColliderComp"){
    this->tileSize = tileSize;
}

float ColliderComp::getX(){
    cout << "getX" << endl;
    return owner->getSprite()->getPosition().x - tileSize/2;
}

float ColliderComp::getY(){
    cout << "getY" << endl;
    return owner->getSprite()->getPosition().y - tileSize/2;
}

float ColliderComp::getWidth(){
    cout << "getW" << endl;
    return owner->getSprite()->getTextureRect().size.x;
}

float ColliderComp::getHeight(){
    cout << "getH" << endl;
    return owner->getSprite()->getTextureRect().size.y;
}