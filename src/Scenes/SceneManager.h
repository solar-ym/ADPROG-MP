#pragma once

#include "Scene.h"

class SceneManager{
    public:
        enum SCENE_ID {SCREEN_starting, SCREEN_round1, SCREEN_ending};

        SceneManager() { currentScene = -1; }
	    // static SceneManager* createInstance() {
	    //     if(myInstance == nullptr)
        //         myInstance = new SceneManager();
        //     return myInstance;
	    // }
	    
        //@! Loading Scenes
        //There should be a way for the manager to load scenes.
        void registerScene(Scene* scene){
            scenes.push_back(scene);
	    }
        Scene* loadScene(SCENE_ID id){
            cout << "ID Recieved: " << id << endl;
            if(-1!=currentScene && id!=currentScene)
                scenes[currentScene]->onUnload();
            currentScene = id;
            cout << "currentScene Recieved: " << currentScene << endl;
            scenes[currentScene]->onLoad();
            return scenes[currentScene];
        }
	    //@!e
	    
	    void updateCurrentScene(Time deltaTime){
        // cout << "attempting to update" << endl;
	        if(-1!=currentScene)
	            scenes[currentScene]->update();
	    }
	    void drawCurrentScene(RenderWindow *window){
            // cout << "attempting to draw" << endl;
	        if(-1!=currentScene)
	            scenes[currentScene]->draw(window);
	    }
	    ~SceneManager(){ 
	        for(Scene* s: scenes) delete s;
	    }

        int getCurrentScene() {
            return currentScene;
        }
    private:
        static SceneManager* myInstance;
        vector<Scene*> scenes;
        int currentScene;
        // SceneManager(){ currentScene = -1; }
};