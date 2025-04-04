#pragma once

#include "Scene.h"

class SceneManager {
    public:
        enum SCENE_ID {SCREEN_starting, SCREEN_round1, SCREEN_ending};

        SceneManager();

        //@! Loading Scenes
        //There should be a way for the manager to load scenes.
        void registerScene(Scene* scene);
        void loadScene(SCENE_ID id);
	    //@!e

        void reloadBattle(int id);
	    
	    void updateCurrentScene();
	    void drawCurrentScene(RenderWindow *window);
        int getCurrentScene();
        Scene* getSpecificScene(SCENE_ID id);

        ~SceneManager();
    private:
        static SceneManager* myInstance;
        vector<Scene*> scenes;
        int currentScene;
};