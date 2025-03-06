#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"
#include "../Objects/Drillku.h"

class Game: public BaseEngine{
    private:
        /* START OF TESTING ONLY */
        Texture text; Sprite* sprite_test;
        Texture bg;   Sprite* background;
        // Texture dirt; Sprite* dirt_sprite;
        /* END OF TESTING ONLY */

        Drillku* player;
    public:
        void init();
        void update(Time deltaTime);
        void draw(RenderWindow *window);
        void keyPressTrigger(Keyboard::Scan keyCode);
        void keyReleaseTrigger(Keyboard::Scan keyCode);
        ~Game();
};