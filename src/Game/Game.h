#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"

class Game: public BaseEngine{
    private:
        /* START OF TESTING ONLY */
        Texture text; Sprite* sprite_test;
        Texture bg;   Sprite* background;
        /* END OF TESTING ONLY */
    public:
        void init();
        void update(Time deltaTime);
        void draw(RenderWindow *window);
        void keyPressTrigger(Keyboard::Scan keyCode);
        void keyReleaseTrigger(Keyboard::Scan keyCode);
        ~Game();
};