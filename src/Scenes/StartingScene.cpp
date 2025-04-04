#include "StartingScene.h"

StartingScene::StartingScene(string name) : Scene(name) {}

void StartingScene::onLoad() {
    Background* bg = new Background("BG_start", 1);
    UIAsset* startButton = new UIAsset("START_off", {83.7f, 494.2f});
    UIAsset* exitButton = new UIAsset("EXIT_off", {83.7f, 587.8f});

    addObject(bg);  
    addObject(startButton);
    addObject(exitButton);
}

void StartingScene::onUnload() {
    removeAllObjects();
}

void StartingScene::reloadRoundData() {}
void StartingScene:: setRoundNum(int id) {} 

void StartingScene::toggleOnStart(){ 
    isOnStart = !isOnStart;
}

bool StartingScene::getOnStart(){ return isOnStart; }

void StartingScene::update() {
    UIAsset* startButton = (UIAsset*)getAllObjects()[START_BUTTON];
    UIAsset* exitButton  = (UIAsset*)getAllObjects()[EXIT_BUTTON];
    internalTime++;
    
    if (internalTime == 60) {
        //I feel like might need to restart the texture if i switch from it when its toggled on
        if (!toggleButtonState) {
            if(isOnStart){
                startButton->changeTexture("START_on");
                exitButton->changeTexture("EXIT_off");
            }
            else {
                exitButton->changeTexture("EXIT_on");
                startButton->changeTexture("START_off");
            }
            toggleButtonState = !toggleButtonState;
        } else {
            if(isOnStart)
                startButton->changeTexture("START_off");
            else 
                exitButton->changeTexture("EXIT_off");
                
            toggleButtonState = !toggleButtonState;
        }
        internalTime = 0;
    }
}
