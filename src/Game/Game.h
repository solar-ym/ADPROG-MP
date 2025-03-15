#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"
#include "../Objects/Drillku.h"
#include "../Objects/Veggie.h"
#include "../Scenes/SceneManager.h"

class Game: public BaseEngine{
    private:
        // TEMPORARY    
            Texture bg;   Sprite* background;
            Drillku* player;

        SceneManager* sceneManager;
        vector<Veggie*> fruitList;
    public:
        void init();
        void update(Time deltaTime);
        void draw(RenderWindow *window);
        void keyPressTrigger(Keyboard::Scan keyCode);
        void keyReleaseTrigger(Keyboard::Scan keyCode);

        void initializeVeggieList();

        ~Game();
};