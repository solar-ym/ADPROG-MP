#pragma once

#include "Scene.h"

class StartingScene : public Scene {
    private:
        enum objIndex {BACKGROUND, BUTTON, ARROW};
        int internalTime = 0;
        bool toggleButtonState = false;
    public:
        StartingScene(string name) : Scene(name) {}

        void onLoad() {
            cout << "Attempting to load Starting Screen" << endl;
            // GameObject* bg = new Background();
            Background* bg  = new Background();
            bg->manualCreation("../../sprites/TEMP_start/TEMP_StartingScreen.png");
            // GameObject* background = bg;

            cout << "[STARTING SCREEN] Background created" << endl;

            UIAsset* startButton = new UIAsset();
            startButton->manualCreation("../../sprites/TEMP_start/TEMP_startButton2.png", 140.f, 450.f);
            // GameObject* button = startButton;

            cout << "[STARTING SCREEN] Button created" << endl;

            UIAsset* selection = new UIAsset();
            selection->manualCreation("../../sprites/TEMP_start/TEMP_selectArrow.png", 140.f, 450.f);
            // GameObject* select = selection;

            cout << "[STARTING SCREEN] Arrow created" << endl;

            addObject(bg);  addObject(startButton);
            addObject(selection);

            cout << "[STARTING SCREEN] Objects pushed" << endl;
            /*
                addObject(new Background(""))
            */
        }

        void onUnload() {
            removeAllObjects();
        }

        void update() {
            internalTime++;
            if (internalTime == 60) {
                cout << "Altering texture" << endl;
                UIAsset* buttonState = (UIAsset*)getAllObjects()[BUTTON];

                if (!toggleButtonState) {
                    buttonState->changeTexture("../../sprites/TEMP_start/TEMP_startButton1.png");
                    toggleButtonState = !toggleButtonState;
                } else {
                    buttonState->changeTexture("../../sprites/TEMP_start/TEMP_startButton2.png");
                    toggleButtonState = !toggleButtonState;
                }
                internalTime = 0;
                cout << "   > Success" << endl;
            }
        }

};