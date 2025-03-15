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

class Entity : public GameObject {
    public:
        Entity() {}
        Entity(string name) : GameObject(name) {}
        
        void initialize() {};
        void update() {};
        void draw(RenderWindow *window) {};
};