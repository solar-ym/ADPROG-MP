#include "MovementComp.h"

MovementComp :: MovementComp() {}

MovementComp :: MovementComp(string name, ENTITY_TYPE entType, Sprite* ownerSprite) 
    : Component(name) {  
        ownerEntType = entType;
        this->ownerSprite = ownerSprite;
        originalTexRec = ownerSprite->getTextureRect();
        if (ownerEntType == ENTITY_TYPE::ENEMY)
            speed = 1.0f;
}

void MovementComp :: move() {
    if (isMoving) {
        switch (movementType) {
            case UP:
            // ROTATION
                if (ownerSprite->getRotation() == degrees(0) && !isFlipped)
                    ownerSprite->setRotation(degrees(270));
                else if (ownerSprite->getRotation() == degrees(0) && isFlipped)
                    ownerSprite->setRotation(degrees(90));
                else if (ownerSprite->getRotation() == degrees(90) && !isFlipped) 
                    invertTexture();
                else if (ownerSprite->getRotation() == degrees(270) && isFlipped) {
                    invertTexture();
                }
            // MOVEMENT
                if (owner->getSprite()->getPosition().y > (TILE_SIZE * 2)+(TILE_SIZE/2))
                    ownerSprite->move(Vector2f(0, -speed));
                break;
            case DOWN:
                if (ownerSprite->getRotation() == degrees(0) && !isFlipped)
                    ownerSprite->setRotation(degrees(90));
                else if (ownerSprite->getRotation() == degrees(0) && isFlipped)
                    ownerSprite->setRotation(degrees(270));
                else if (ownerSprite->getRotation() == degrees(270) && !isFlipped) {
                    invertTexture();
                }
                else if (ownerSprite->getRotation() == degrees(90) && isFlipped)
                    invertTexture();

                if (owner->getSprite()->getPosition().y < (TILE_SIZE * 14)-(TILE_SIZE/2))
                    ownerSprite->move(Vector2f(0, speed));
                break;
            case LEFT:
                ownerSprite->setRotation(degrees(0));
                if (!isFlipped) invertTexture();

                if (owner->getSprite()->getPosition().x > (TILE_SIZE/2))
                    ownerSprite->move(Vector2f(-speed, 0));
            break;
            case RIGHT:
                ownerSprite->setRotation(degrees(0));
                if (isFlipped) invertTexture();

                if (owner->getSprite()->getPosition().x < (TILE_SIZE * 14)-(TILE_SIZE/2))
                    ownerSprite->move(Vector2f(speed, 0));
            break;
        }
    }
}


void MovementComp :: reCenter(MOVE_TYPE from) {
    // if (owner->getName() == "Geygar") cout << "Recentering." << endl;
    int x = owner->getTileX();      float realX = ownerSprite->getPosition().x;
    int y = owner->getTileY();      float realY = ownerSprite->getPosition().y;
    y += 2;

    bool belowY = realY >= (y * TILE_SIZE)+25 && realY <= (y+1 * TILE_SIZE);
    bool aboveY = realY <= (y+1 * TILE_SIZE)-25 && realY >= (y * TILE_SIZE);

    bool leftX = realX <= (x * TILE_SIZE)+25 && realX >= (x * TILE_SIZE);
    bool rightX = realX >= (x+1 * TILE_SIZE)-25 && realX <= (x+1 * TILE_SIZE);

    y -= 2;
    switch (from) {
        case LEFT: 
        case RIGHT:
            if (facing == UP && aboveY)
                owner->setTileXY(x, y-1);
            else if (facing == UP && belowY)
                owner->setTileXY(x, y);
            else if (facing == DOWN && belowY)
                owner->setTileXY(x, y+1);
            else if (facing == DOWN && aboveY)
                owner->setTileXY(x, y);
            else 
                owner->setTileXY(x, y);
            break;
        case UP:
        case DOWN:
            if (facing == LEFT && leftX)
                owner->setTileXY(x, y);
            else if (facing == LEFT && rightX)
                owner->setTileXY(x, y);
            else if (facing == RIGHT && leftX)
                owner->setTileXY(x, y);
            else if (facing == RIGHT && rightX)
                owner->setTileXY(x+1, y);
            else 
                owner->setTileXY(x, y);
            break;
        default: owner->setTileXY(x, y);
            break;
    }
}

void MovementComp :: invertTexture() {
    IntRect texRec = ownerSprite->getTextureRect();

    if (texRec.size.x > 0) {
        ownerSprite->setTextureRect(IntRect({texRec.position.x+texRec.size.x, texRec.position.y}, {-texRec.size.x, texRec.size.y}));
        isFlipped = true;
    }
    else {
        ownerSprite->setTextureRect(originalTexRec);
        isFlipped = false;
    }
}

void MovementComp :: fixInversion() {
    if (isFlipped) {
        IntRect texRec = ownerSprite->getTextureRect();
        if (texRec.size.x > 0) {
            ownerSprite->setTextureRect(IntRect({texRec.position.x+texRec.size.x, texRec.position.y}, {-texRec.size.x, texRec.size.y}));
        }
    }
}

void MovementComp :: setMovingBool(bool value) {
    isMoving = value;
}

void MovementComp :: setMovementType(MOVE_TYPE moveType) {
    movementType = moveType;
    facing = moveType;
}

MovementComp::MOVE_TYPE MovementComp :: isFacing(){
    return facing;
}

bool MovementComp :: checkFlipped() {
    return isFlipped;
}

bool MovementComp :: getIsMoving() {
    return isMoving;
}