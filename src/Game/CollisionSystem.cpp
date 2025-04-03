#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {}
void CollisionSystem::listen(Scene* scene, vector<Enemy*> enemies, Drillku* player) {
    if (internalTime > 90) {
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

void CollisionSystem::onPlayerCollision(Scene* scene, Drillku* player, Enemy* enemy) {
    if (internalTime == 0) {
        player->kill();
        running = true;
    }
}

bool CollisionSystem::collisionComputation(ColliderComp* obj1, ColliderComp* obj2 ) { 
    return obj1->getX() < obj2->getX() + obj2->getWidth() &&
            obj2->getX() < obj1->getX() + obj1->getWidth() &&
            obj1->getY() < obj2->getY() + obj2->getHeight() &&
            obj2->getY() < obj1->getY() + obj1->getHeight();
}

bool CollisionSystem::forcefulComputation(Drillku* player, Enemy* enemy) { 
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

void CollisionSystem::update() {
    if (running && internalTime < 100) internalTime++;
}

void CollisionSystem::onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy){
    if (enemy->getIsDead()) {
        enemy->setTileXY(999,999);
    } else {
        enemy->kill();
    }
}
