#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"

#include "../Objects/Drillku.h"
#include "../Objects/Veggie.h"
#include "../Objects/Background.h"

#include "../Scenes/SceneManager.h"
#include "../Scenes/StartingScene.h"
#include "../Scenes/BattleScene.h"

class Game: public BaseEngine{
    private:
        // TEMPORARY    
            Drillku* player;
            Background* background;

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