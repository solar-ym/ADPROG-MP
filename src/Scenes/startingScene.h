#pragma once

#include "Scene.h"
#include "../Objects/Background.h"
#include "../Objects/UIAsset.h"

// Starting menu. Identical in structure to the ending screen
class StartingScene : public Scene {
    private:
        enum objIndex {BACKGROUND, START_BUTTON, EXIT_BUTTON};
        int internalTime = 0;
        bool toggleButtonState = false;
        bool isOnStart = true;
    public:
        StartingScene(string name);

        void onLoad();
        void onUnload();

        void reloadRoundData();
        void setRoundNum(int id);

        void toggleOnStart();
        bool getOnStart();

        void update();
};