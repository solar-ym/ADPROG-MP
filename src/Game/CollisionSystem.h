#pragma once

#include "../Scenes/Scene.h"
#include "../Objects/Entity.h"

class CollisionSystem{
    public:
        void listen(Scene* scene){
            std::vector<GameObject*> objects = scene->getAllObjects();
            for(int i=0; i<objects.size()-1; i++){
            
                Entity* obj1 = dynamic_cast<Entity*>(objects[i]);
                if(obj1==nullptr) continue;
                // if(obj1->getComponent("ACO_ColliderComp")==nullptr) continue;
                
                for(int j=i+1; j<objects.size(); j++){
                    Entity* obj2 = dynamic_cast<Entity*>(objects[j]);
                    if(obj2==nullptr) continue;
                    // if(obj2->getComponent("ACO_ColliderComp")==nullptr) continue;
                    
                    if(     obj1->getTileX()==obj2->getTileX() && 
                            obj1->getTileY()==obj2->getTileY())
                        onCollision(scene,obj1,obj2);
                }//end for
            }//end for
        }
        
        void onCollision(Scene* scene, Entity* obj1, Entity* obj2){
            if(obj1->getName()=="player"){
                onPlayerCollision(scene,obj1,obj2);
            }else if(obj2->getName()=="player"){
                onPlayerCollision(scene,obj2,obj1);
            }else if(obj1->getName().rfind("bullet",0)==0 || obj1->getName().rfind("side",0)==0){
                onBulletCollision(scene,obj1,obj2);
            }else if(obj2->getName().rfind("bullet",0)==0 || obj2->getName().rfind("side",0)==0){
                onBulletCollision(scene,obj2,obj1);
            }
        }
        
        void onPlayerCollision(Scene* scene, Entity* player, 
                Entity* other){
            if(other->getName().rfind("enemy",0)==0){
 
            }else if(other->getName().rfind("bonus",0)==0){

            }else if(other->getName().rfind("bullet",0)==0){

            }
        }
        
        void onBulletCollision(Scene* scene, Entity* bullet, 
                Entity* other){
            if(other->getName().rfind("enemy",0)==0){

                bullet->setTileXY(999,999);
            }else if(other->getName().rfind("bonus",0)==0){

            }
        }

};