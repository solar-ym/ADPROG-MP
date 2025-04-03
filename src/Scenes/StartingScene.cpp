#include "StartingScene.h"

StartingScene::StartingScene(string name) : Scene(name) {}

void StartingScene::onLoad() {
    Background* bg  = new Background();
    bg->manualCreation("../../sprites/TEMP_start/TEMP_StartingScreen.png");
    
    UIAsset* startButton = new UIAsset();
    startButton->manualCreation("../../sprites/TEMP_start/TEMP_startButton2.png", 140.f, 450.f);
    
    UIAsset* selection = new UIAsset();
    selection->manualCreation("../../sprites/TEMP_start/TEMP_selectArrow.png", 140.f, 450.f);
    
    addObject(bg);  addObject(startButton);
    addObject(selection);
}

void StartingScene::onUnload() {
    removeAllObjects();
}

void StartingScene::reloadRoundData() {}
void StartingScene:: setRoundNum(int id) {} 

void StartingScene::update() {
    internalTime++;
    if (internalTime == 60) {
        UIAsset* buttonState = (UIAsset*)getAllObjects()[BUTTON];

        if (!toggleButtonState) {
            buttonState->changeTexture("../../sprites/TEMP_start/TEMP_startButton1.png");
            toggleButtonState = !toggleButtonState;
        } else {
            buttonState->changeTexture("../../sprites/TEMP_start/TEMP_startButton2.png");
            toggleButtonState = !toggleButtonState;
        }
        internalTime = 0;
    }
}
