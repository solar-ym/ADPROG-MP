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
                if(forcefulComputation(player, enemies[i]) && player->getAtkComp()->isVisible())
                   onAttackCollision(scene, player, enemies[i]);
                else
                    enemies[i]->setIsDying(false);
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

        bool forcefulComputation(Drillku* player, Enemy* enemy) { 
            EntityAttack* attSprite = player->getAttackSprite();
            AttackComp* att = player->getAtkComp();
            switch (player->getMoveComp()->isFacing()) {
                case MovementComp::UP:
                    if (enemy->getTileX() == att->getAttX() &&
                        enemy->getTileY() <= att->getAttY() && 
                        enemy->getTileY() >= att->getAttY() - (attSprite->getTextRect_X()/TILE_SIZE))
                        return true;
                    break;
                case MovementComp::DOWN:
                    if (enemy->getTileX() == att->getAttX() &&
                        enemy->getTileY() >= att->getAttY() && 
                        enemy->getTileY() <= att->getAttY() + (attSprite->getTextRect_X()/TILE_SIZE))
                        return true;
                    break;
                case MovementComp::LEFT:
                    if (enemy->getTileY() == att->getAttY() &&
                        enemy->getTileX() <= att->getAttX() && 
                        enemy->getTileX() >= att->getAttX() - (attSprite->getTextRect_X()/TILE_SIZE))
                        return true;
                    break;
                case MovementComp::RIGHT:
                    if (enemy->getTileY() == att->getAttY() &&
                        enemy->getTileX() >= att->getAttX() && 
                        enemy->getTileX() <= att->getAttX() + (attSprite->getTextRect_X()/TILE_SIZE))
                        return true;
                    break;
            }
            return false;
        }

        void update() {
            if (running && internalTime < 100) internalTime++;
        }
        
        void onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy){
            if (enemy->getIsDead()) {
                enemy->setTileXY(999,999);
            } else {
                enemy->kill();
            }
            
            // else if (other->getName() == "Geygar") {
            // }
            
            // else if(other->getName().rfind("bonus",0)==0){

            // }else if(other->getName().rfind("bullet",0)==0){

            // }
        }

};