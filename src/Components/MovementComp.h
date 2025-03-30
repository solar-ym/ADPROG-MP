#pragma once

#include "Component.h"
#include "../Objects/Drillku.h"

class MovementComp : public Component {
    public:
        enum MOVE_TYPE {UP, DOWN, LEFT, RIGHT};
        enum ENTITY_TYPE {ENEMY, PLAYER};

        MovementComp();
        MovementComp(string name, ENTITY_TYPE entType, Sprite* ownerSprite);

        void move();
        void reCenter(MOVE_TYPE from);
        // MOVE_TYPE reCenter(MOVE_TYPE from);
        void invertTexture();
        void fixInversion();

        void setMovingBool(bool value);
        void setMovementType(MOVE_TYPE moveType);
        
        MOVE_TYPE isFacing();
        bool checkFlipped();
        bool getIsMoving();
    private:
        ENTITY_TYPE ownerEntType;
        Sprite* ownerSprite;
        bool isMoving = false;
        MOVE_TYPE movementType;

        float speed = 2.0f;
        IntRect originalTexRec;
        bool isFlipped = false;
        MOVE_TYPE facing = RIGHT;
};