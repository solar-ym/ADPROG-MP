#pragma once

#include "Scene.h"
#include "../Objects/Background.h"
#include "../Objects/UIAsset.h"

class EndingScreen : public Scene {
    private:
        enum objIndex {BACKGROUND, MENU_BUTTON, EXIT_BUTTON};
        int internalTime = 0;
        bool toggleButtonState = false;
        bool isOnStart = true;
    public:
        EndingScreen(string name);

        void onLoad();
        void onUnload();

        void reloadRoundData();
        void setRoundNum(int id);

        void toggleOnStart();
        bool getOnStart();

        void update();
};