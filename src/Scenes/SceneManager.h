#pragma once

#include "Scene.h"

// from class

class SceneManager {
    public:
        enum SCENE_ID {SCREEN_starting, SCREEN_battle, SCREEN_ending, SCREEN_loss};

        SceneManager();

        //@! Loading Scenes
        //There should be a way for the manager to load scenes.
        void registerScene(Scene* scene);
        void loadScene(SCENE_ID id); // made this not return anything since it was not being used that way
	    //@!e

        void reloadBattle(int id);
	    
	    void updateCurrentScene();
	    void drawCurrentScene(RenderWindow *window);
        int getCurrentScene();

        // added the below for utility
        Scene* getSpecificScene(SCENE_ID id);
        Scene* getSpecificScene(int id);

        ~SceneManager();
    private:
        static SceneManager* myInstance;
        vector<Scene*> scenes;
        int currentScene = -1;
};