#include "SpriteManip.h"

void SpriteManip::moveUp(Tunnel* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() - 1; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveDown(Tunnel* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() + 1; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveLeft(Tunnel* obj){
    int x = obj->getTileX() - 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveRight(Tunnel* obj){
    int x = obj->getTileX() + 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
}

void SpriteManip::turnLeft(Tunnel* obj){
    obj->getSprite()->rotate(degrees(-90));
}

void SpriteManip::turnRight(Tunnel* obj){
    obj->getSprite()->rotate(degrees(90));
}

void SpriteManip::moveToRand(Tunnel* obj,int gridSize){
    int xPos = rand()%gridSize;
    int yPos = rand()%gridSize;
    obj->setTileXY(xPos,yPos);
}

