#pragma once

#include "Scene.h"
#include "../Objects/Background.h"
#include "../Objects/UIAsset.h"

class StartingScene : public Scene {
    private:
        enum objIndex {BACKGROUND, BUTTON, ARROW};
        int internalTime = 0;
        bool toggleButtonState = false;
    public:
        StartingScene(string name);

        void onLoad();
        void onUnload();

        void reloadRoundData();

        void update();
};