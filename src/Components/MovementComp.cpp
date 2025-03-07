#include "MovementComp.h"

MovementComp :: MovementComp() {}

MovementComp :: MovementComp(string name, ENTITY_TYPE entType, Sprite* ownerSprite) 
    : Component("name") {  
        ownerEntType = entType;
        this->ownerSprite = ownerSprite;
}

void MovementComp :: move(MOVE_TYPE moveType) {
    switch (moveType) {
        case UP:
            // ownerSprite->setOrigin({25,25});
            // if (ownerSprite->getRotation() == degrees(0)) {
            //     ownerSprite->setRotation(degrees(270));
            // }
            // ownerSprite->setOrigin({0,0});

            if (ownerSprite->getPosition().y != TILE_SIZE)
                ownerSprite->move(Vector2f(0, -10.0f));
            break;
        case DOWN:
            if (ownerSprite->getPosition().y != (DIRT_HEIGHT + 1) * TILE_SIZE)
                ownerSprite->move(Vector2f(0, 10.0f));
            break;
        case LEFT:
            if (ownerSprite->getPosition().x != 0.0f)
                ownerSprite->move(Vector2f(-10.0f, 0));
            break;
        case RIGHT:
            if (ownerSprite->getPosition().x != (DIRT_WIDTH - 1) * TILE_SIZE)
                ownerSprite->move(Vector2f(10.0f, 0));
            break;
    }
}