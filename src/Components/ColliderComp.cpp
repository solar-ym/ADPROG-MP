#include "ColliderComp.h"

ColliderComp::ColliderComp(float tileSize):
        Component("ColliderComp"){
    this->tileSize = tileSize;
}

float ColliderComp::getX(){
    Entity* owner = getOwner();
    return owner->getSprite()->getPosition().x - tileSize/2;
}

float ColliderComp::getY(){
    Entity* owner = getOwner();
    return owner->getSprite()->getPosition().y - tileSize/2;
}

float ColliderComp::getWidth(){
    Entity* owner = getOwner();
    return owner->getSprite()->getScale().x * tileSize;
}

float ColliderComp::getHeight(){
    Entity* owner = getOwner();
    return owner->getSprite()->getScale().y * tileSize;
}