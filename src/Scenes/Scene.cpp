#include "Scene.h"

Scene::Scene(string name){ this->name=name; }
Scene::~Scene(){ for(GameObject* obj: objects) delete obj; }
string Scene::getName(){ return name; }

//@! Scene's Update and Draw
//Depending on the scene's implementation, it too may have
//its own update and draw functions.
void Scene::update(){
    for(GameObject* obj: objects)
        obj->update();
}
void Scene::draw(RenderWindow* window){
    for(GameObject* obj: objects)
        obj->draw(window);
}

//@! Adding and removing Objects
//There should be a way to add, remove and find objects from
//a scene.
void Scene::addObject(GameObject* obj){
    objects.push_back(obj);
}
GameObject* Scene::findObject(string id){
    for(GameObject* obj: objects)
        if(obj->getName() == id)
            return obj;
    return nullptr;
}

//@! Adding and removing Objects (cont)
vector<GameObject*> Scene::getAllObjects(){
    return objects;
}
void Scene::removeAllObjects(){
    for(GameObject* obj: objects)
        delete obj;
    objects.clear();
}
