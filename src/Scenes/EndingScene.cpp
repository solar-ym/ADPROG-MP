#include "EndingScene.h"

EndingScreen::EndingScreen(string name) : Scene(name) {}

void EndingScreen::onLoad() {

    if (getName() == "Lose Screen")
        addObject(new Background("BG_lose", 1));
    else
        addObject(new Background("BG_win", 1));


    UIAsset* menuButton = new UIAsset("MENU_on", {254.8f, 413.1f});
    UIAsset* exitButton = new UIAsset("EXIT_off", {254.8f, 506.7f});

      
    addObject(menuButton);
    addObject(exitButton);
}

void EndingScreen::onUnload() {
    removeAllObjects();
    internalTime = 0;
    toggleButtonState = false;
    isOnStart = true;
}

void EndingScreen::reloadRoundData() {}
void EndingScreen:: setRoundNum(int id) {} 

void EndingScreen::toggleOnStart(){ 
    isOnStart = !isOnStart;
    UIAsset* menuButton = (UIAsset*)getAllObjects()[MENU_BUTTON];
    UIAsset* exitButton  = (UIAsset*)getAllObjects()[EXIT_BUTTON];

    if (isOnStart) {
        menuButton->changeTexture("MENU_off");
        exitButton->changeTexture("EXIT_off");
    } else {
        exitButton->changeTexture("EXIT_on");
        menuButton->changeTexture("MENU_on");
    }

    toggleButtonState = true;
}

bool EndingScreen::getOnStart(){ return isOnStart; }

void EndingScreen::update() {
    UIAsset* menuButton = (UIAsset*)getAllObjects()[MENU_BUTTON];
    UIAsset* exitButton  = (UIAsset*)getAllObjects()[EXIT_BUTTON];
    internalTime++;
    
    if (internalTime > 60) {
        if (toggleButtonState) {
            if (isOnStart) {
                menuButton->changeTexture("MENU_off");
            } else {
                exitButton->changeTexture("EXIT_on");
            }
        } else {
            if (isOnStart) {
                menuButton->changeTexture("MENU_on");
            } else {
                exitButton->changeTexture("EXIT_off");
            }
        }
        internalTime = 0;
    }

    toggleButtonState = !toggleButtonState;
}
