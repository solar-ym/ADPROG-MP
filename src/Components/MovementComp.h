#pragma once

#include "Component.h"

class MovementComp : public Component {
    public:
        enum MOVE_TYPE {UP, DOWN, LEFT, RIGHT};
        enum ENTITY_TYPE {ENEMY, PLAYER};

        MovementComp();
        MovementComp(string name, ENTITY_TYPE entType, Sprite* ownerSprite);

        void move(MOVE_TYPE moveType);
    private:
        ENTITY_TYPE ownerEntType;
        Sprite* ownerSprite;
};