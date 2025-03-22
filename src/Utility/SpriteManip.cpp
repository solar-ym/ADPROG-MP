#include "SpriteManip.h"

void SpriteManip::moveUp(Entity* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() - 1; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveDown(Entity* obj){
    int x = obj->getTileX() + 0;
    int y = obj->getTileY() + 1; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveLeft(Entity* obj){
    int x = obj->getTileX() - 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
}

void SpriteManip::moveRight(Entity* obj){
    int x = obj->getTileX() + 1;
    int y = obj->getTileY() + 0; 
    obj->setTileXY(x,y);
}

void SpriteManip::turnLeft(Entity* obj){
    obj->getSprite()->rotate(degrees(-90));
}

void SpriteManip::turnRight(Entity* obj){
    obj->getSprite()->rotate(degrees(90));
}

void SpriteManip::moveToRand(Entity* obj,int gridSize){
    int xPos = rand()%gridSize;
    int yPos = rand()%gridSize;
    obj->setTileXY(xPos,yPos);
}

