#pragma once

#include "../Utility/configurations.h"
#include "../Game/GD_GameResource.h"
#include "GameObject.h"
/*
    ANIMATED
    player
    enemies

    SEMI ANIMATED
    rock
    attacks
    
    NOT ANIMATED
    fruits
    flowers
*/

class ColliderComp;

class Entity : public GameObject {
    public:
        Entity();
        Entity(string name);

        virtual void setTileXY(int xV, int yV) = 0;
        virtual int getTileX() = 0;
        virtual int getTileY() = 0;

        virtual Sprite* getSprite() = 0;
        
        void initialize();
        void update();
        void draw(RenderWindow *window);
};