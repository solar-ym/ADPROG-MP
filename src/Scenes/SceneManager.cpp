#include "SceneManager.h"

SceneManager :: SceneManager () {
    currentScene = -1;
}

void SceneManager :: registerScene(Scene* scene){
    scenes.push_back(scene);
}

Scene* SceneManager :: loadScene(SCENE_ID id) {
    cout << "ID Recieved: " << id << endl;
    if(-1!=currentScene && id!=currentScene)
        scenes[currentScene]->onUnload();
    currentScene = id;
    cout << "currentScene Recieved: " << currentScene << endl;
    scenes[currentScene]->onLoad();
    return scenes[currentScene];
}

void SceneManager :: reloadBattle(int id) {
    if (scenes[currentScene]->getName() == "Battle Screen") {
        scenes[currentScene]->setRoundNum(id);
        scenes[currentScene]->reloadRoundData();
    }
}

void SceneManager :: updateCurrentScene(){
    // cout << "attempting to update" << endl;
    if(-1!=currentScene)
        scenes[currentScene]->update();
}

void SceneManager :: drawCurrentScene(RenderWindow *window) {
    // cout << "attempting to draw" << endl;
    if(-1!=currentScene)
        scenes[currentScene]->draw(window);
}

int  SceneManager :: getCurrentScene() {
    return currentScene;
}

SceneManager :: ~SceneManager() { 
    scenes[currentScene]->onUnload();
    for(Scene* s: scenes) delete s;
}