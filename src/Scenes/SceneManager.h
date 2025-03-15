#pragma once

#include "Scene.h"

class SceneManager{
    public:
        enum SCENE_ID {SCREEN_starting, SCREEN_round1, SCREEN_ending};

	    static SceneManager* createInstance() {
	        if(myInstance == nullptr)
                myInstance = new SceneManager();
            return myInstance;
	    }
	    
        //@! Loading Scenes
        //There should be a way for the manager to load scenes.
        void registerScene(Scene* scene){
            scenes.push_back(scene);
	    }
        Scene* loadScene(SCENE_ID id){
            if(-1!=currentScene && id!=currentScene)
                scenes[currentScene]->onUnload();
            currentScene = id;
            scenes[currentScene]->onLoad();
            return scenes[currentScene];
        }
	    //@!e
	    
	    void updateCurrentScene(Time deltaTime){
	        if(-1!=currentScene)
	            scenes[currentScene]->update();
	    }
	    void drawCurrentScene(RenderWindow *window){
	        if(-1!=currentScene)
	            scenes[currentScene]->draw(window);
	    }
	    ~SceneManager(){ 
	        for(Scene* s: scenes) delete s;
	    }
    private:
        static SceneManager* myInstance;
        vector<Scene*> scenes;
        int currentScene;
        SceneManager(){ currentScene = -1; }
};