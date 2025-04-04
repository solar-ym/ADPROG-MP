#include "SceneManager.h"

SceneManager :: SceneManager () {
    currentScene = -1;
}

void SceneManager :: registerScene(Scene* scene){
    scenes.push_back(scene);
}

void SceneManager :: loadScene(SCENE_ID id) {
    if(-1!=currentScene && id!=currentScene)
        scenes[currentScene]->onUnload();
    currentScene = id;

    scenes[currentScene]->onLoad();
}

void SceneManager :: reloadBattle(int id) {
    if (scenes[currentScene]->getName() == "Battle Screen") {
        scenes[currentScene]->setRoundNum(id);
        scenes[currentScene]->reloadRoundData();
    }
}

void SceneManager :: updateCurrentScene(){
    if(-1!=currentScene)
        scenes[currentScene]->update();
}

void SceneManager :: drawCurrentScene(RenderWindow *window) {
    if(-1!=currentScene)
        scenes[currentScene]->draw(window);
}

int  SceneManager :: getCurrentScene() {
    return currentScene;
}

Scene* SceneManager :: getSpecificScene(SCENE_ID id){
    return scenes[id];
}

Scene* SceneManager :: getSpecificScene(int id){
    return scenes[id];
}

SceneManager :: ~SceneManager() { 
    scenes[currentScene]->onUnload();
    for(Scene* s: scenes) delete s;
}
