#include "SceneManager.h"

SceneManager :: SceneManager () {
    currentScene = -1;
}

void SceneManager :: registerScene(Scene* scene){
    scenes.push_back(scene);
}

Scene* SceneManager :: loadScene(SCENE_ID id) {
    if(-1!=currentScene && id!=currentScene)
        scenes[currentScene]->onUnload();
    currentScene = id;

    scenes[currentScene]->onLoad();
    return scenes[currentScene];
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

SceneManager :: ~SceneManager() { 
    scenes[currentScene]->onUnload();
    for(Scene* s: scenes) delete s;
}