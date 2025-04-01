#pragma once

#include "../Utility/configurations.h"
#include "../Objects/Background.h"
#include "../Objects/UIAsset.h"
#include "../ObjectManipulation/Factories/Factories.h"
#include "../Utility/SpriteManip.h"

class Scene{
    private:
        string name;
        vector<GameObject*> objects;
    public:
        Scene(string name){ this->name=name; }
        ~Scene(){ for(GameObject* obj: objects) delete obj; }
        string getName(){ return name; }
        
        //@! Scene Load and Unload
        //Each scene should have a load and unload functions which
        //are triggered when the scene is loaded or unloaded by the
        //game. These functions should be in charge of the objects
        //on the scene.
        virtual void onLoad() = 0;
        virtual void onUnload() = 0;
        virtual void reloadRoundData() = 0;
        
        //@! Scene's Update and Draw
        //Depending on the scene's implementation, it too may have
        //its own update and draw functions.
        virtual void update(){
            for(GameObject* obj: objects)
                obj->update();
        }
        virtual void draw(RenderWindow* window){
            // cout << "[scene] attempting to draw" << endl;
            for(GameObject* obj: objects)
                obj->draw(window);
        }
        
        //@! Adding and removing Objects
        //There should be a way to add, remove and find objects from
        //a scene.
        void addObject(GameObject* obj){
            objects.push_back(obj);
        }
        GameObject* findObject(string id){
            for(GameObject* obj: objects)
                if(obj->getName() == id)
                    return obj;
            return nullptr;
        }
        
        //@! Adding and removing Objects (cont)
        vector<GameObject*> getAllObjects(){
            return objects;
        }
        void removeAllObjects(){
            for(GameObject* obj: objects)
                delete obj;
            objects.clear();
        }
        //@!e
};