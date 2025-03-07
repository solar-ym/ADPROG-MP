#pragma once

#include "../Utility/configurations.h"

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

class Entity {
    protected:
        String entName;
    // variables that change
    public:
        Entity() {}
        Entity(string name) {
            entName = name;
        }
        
        // virtual void update() = 0;
        virtual void draw(RenderWindow *window) = 0;
        virtual Sprite* getEntSprite() = 0;
};