#pragma once

#include "../Utility/configurations.h"
#include "../ObjectManipulation/Factories/Factories.h"

// from class 
class Scene{
    private:
        string name;
        vector<GameObject*> objects;
    public:
        Scene(string name);
        ~Scene();
        string getName();
        
        virtual void onLoad() = 0;
        virtual void onUnload() = 0;
        // added these two below
        virtual void reloadRoundData() = 0;
        virtual void setRoundNum(int id) = 0;
        
        virtual void update();
        virtual void draw(RenderWindow* window);
        
        void addObject(GameObject* obj);
        GameObject* findObject(string id);
        
        vector<GameObject*> getAllObjects();
        void removeAllObjects();
};