#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"
#include "../Objects/Drillku.h"

class Game: public BaseEngine{
    private:
        Texture bg;   Sprite* background;

        Drillku* player;
    public:
        void init();
        void update(Time deltaTime);
        void draw(RenderWindow *window);
        void keyPressTrigger(Keyboard::Scan keyCode);
        void keyReleaseTrigger(Keyboard::Scan keyCode);
        ~Game();
};