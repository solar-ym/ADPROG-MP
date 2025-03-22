#include "MovementComp.h"

MovementComp :: MovementComp() {}

MovementComp :: MovementComp(string name, ENTITY_TYPE entType, Sprite* ownerSprite) 
    : Component("name") {  
        ownerEntType = entType;
        this->ownerSprite = ownerSprite;
        originalTexRec = ownerSprite->getTextureRect();
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
                if (ownerSprite->getPosition().y != TILE_SIZE)
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

                if (ownerSprite->getPosition().y != (DIRT_HEIGHT + 1) * TILE_SIZE)
                    ownerSprite->move(Vector2f(0, speed));
                break;
            case LEFT:
                ownerSprite->setRotation(degrees(0));
                if (!isFlipped) invertTexture();

                if (ownerSprite->getPosition().x != 0.0f)
                    ownerSprite->move(Vector2f(-speed, 0));
            break;
            case RIGHT:
                ownerSprite->setRotation(degrees(0));
                if (isFlipped) invertTexture();

                if (ownerSprite->getPosition().x != (DIRT_WIDTH - 1) * TILE_SIZE)
                    ownerSprite->move(Vector2f(speed, 0));
            break;
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

MovementComp::MOVE_TYPE MovementComp :: isFacing(){
    return facing;
}

bool MovementComp :: checkFlipped() {
    return isFlipped;
}