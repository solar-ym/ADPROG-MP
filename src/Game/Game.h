#pragma once

#include "BaseEngine.h"
#include "../Utility/configurations.h"

#include "../Objects/Veggie.h"

#include "../Scenes/SceneManager.h"
#include "../Scenes/StartingScene.h"
#include "../Scenes/BattleScene.h"
#include "../Scenes/EndingScene.h"
#include "../Sounds/AudioManager.h"

class Game: public BaseEngine{
    private:
        int roundNum = 1;
        Drillku* player;
        SceneManager* sceneManager;
        AudioManager* audioManager;
    public:
        void init();
        void update(Time deltaTime);
        void draw(RenderWindow *window);
        void keyPressTrigger(Keyboard::Scan keyCode, RenderWindow *window);
        void keyReleaseTrigger(Keyboard::Scan keyCode);

        void playMusic();

        ~Game();
};