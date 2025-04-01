#pragma once

#include "../Scenes/Scene.h"

class CollisionSystem{
    private: 
        int internalTime = 0;
        bool running = false;
    public:
        CollisionSystem() {}
        void listen(Scene* scene, vector<Enemy*> enemies, Drillku* player) {
            if (internalTime > 90) {
                cout << "Death detected, reloading" << endl;
                scene->reloadRoundData();
                internalTime = 0;
                running = false;
            }
            
            for (int i = 0; i < enemies.size(); i++) {

                if(enemies[i]->getTileX() == player->getTileX() &&
                   enemies[i]->getTileY() == player->getTileY())
                    onPlayerCollision(scene, player, enemies[i]);
                
                if(enemies[i]->getTileX() == player->getAtkComp()->getAttX() &&
                   enemies[i]->getTileY() == player->getAtkComp()->getAttY() &&
                   player->getAtkComp()->isVisible())
                   onAttackCollision(scene, player, enemies[i]);
            }

            update();
        }
        
        void onPlayerCollision(Scene* scene, Drillku* player, Enemy* enemy) {
            if (internalTime == 0) {
                cout << "trying to kill miku" << endl;
                player->kill();
                running = true;
            } 
            // else if(obj1->getName().rfind("bullet",0)==0 || obj1->getName().rfind("side",0)==0){
            //     onBulletCollision(scene,obj1,obj2);
            // }else if(obj2->getName().rfind("bullet",0)==0 || obj2->getName().rfind("side",0)==0){
            //     onBulletCollision(scene,obj2,obj1);
            // }
        }

        void update() {
            if (running && internalTime < 500) internalTime++;
        }
        
        void onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy){
            // if(other->getName() == "Pookie" || other->getName() == "Geygar") {
            //     ((Drillku*)player)->kill();
            // } 
            
            // else if (other->getName() == "Geygar") {
            // }
            
            // else if(other->getName().rfind("bonus",0)==0){

            // }else if(other->getName().rfind("bullet",0)==0){

            // }
            cout << "Encountered attack x enemy collision." << endl;
        }

};