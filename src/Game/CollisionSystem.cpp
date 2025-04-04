#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {}
void CollisionSystem::listen(Scene* scene, vector<Enemy*> enemies, Drillku* player, TunnelManager* manager) {
    if (internalTime > 80) {
        scene->reloadRoundData();
        internalTime = 0;
        running = false;
    }
    
    for (int i = 0; i < enemies.size(); i++) {

        // if(enemies[i]->getTileX() == player->getTileX() &&
        //     enemies[i]->getTileY() == player->getTileY())
        //     onPlayerCollision(scene, player, enemies[i]);
        if(forcefulComputation(player, enemies[i], true) && player->getAtkComp()->isVisible()) {
            enemyCollided = true;
            onAttackCollision(scene, player, enemies[i]);
        }
        else {
            enemyCollided = false;
            enemies[i]->setIsDying(false);
        }

        if (enemies[i]->getAtkComp() != nullptr && forcefulComputation(player, enemies[i], false) 
            && enemies[i]->getAtkComp()->isVisible()) {
            onPlayerCollision(scene, player, enemies[i]);
            onAttackCollision(enemies[i]);
        } 
        
        if (enemies[i]->getAtkComp() != nullptr && collisionComputation(enemies[i], manager) &&
            enemies[i]->getAtkComp()->isVisible())
            onAttackCollision(enemies[i]);
    }

    if (collisionComputation(player, manager) && player->getHairVisibility() && !enemyCollided)
        onAttackCollision(player);

    update();
}

void CollisionSystem::onPlayerCollision(Scene* scene, Drillku* player, Enemy* enemy) {
    if (internalTime == 0) {
        player->kill();
        running = true;
    }
}

bool CollisionSystem::collisionComputation(Entity* attacker, TunnelManager* manager) { 
    AttackComp* attack;     
    MovementComp* move;
    EntityAttack* attSprite;

    if (attacker->getName() == "Player") {
        attack = dynamic_cast<Drillku*>(attacker)->getAtkComp();
        move = dynamic_cast<Drillku*>(attacker)->getMoveComp();
    } else if (attacker->getName() == "Geygar") {
        attack = dynamic_cast<Enemy*>(attacker)->getAtkComp();
        move = dynamic_cast<Enemy*>(attacker)->getMoveComp();
    }

    attSprite = attack->getAttackEntity();

    switch (move->isFacing()) {
        case MovementComp::UP:
            if (!(manager->hasTunnel(attack->getAttX(), attack->getAttY() - (attSprite->getTextRect_X()/TILE_SIZE))))
                return true;
            break;
        case MovementComp::DOWN:
        if (!(manager->hasTunnel(attack->getAttX(), attack->getAttY() + (attSprite->getTextRect_X()/TILE_SIZE))))
                return true;
            break;
        case MovementComp::LEFT:
            if (!(manager->hasTunnel(attack->getAttX() - (attSprite->getTextRect_X()/TILE_SIZE), attack->getAttY())))
                return true;
            break;
        case MovementComp::RIGHT:
            if (!(manager->hasTunnel(attack->getAttX() + (attSprite->getTextRect_X()/TILE_SIZE), attack->getAttY())))
                return true;
            break;
    }

    return false;
}

bool CollisionSystem::forcefulComputation(Drillku* player, Enemy* opponent, bool isPlayer) { 
    EntityAttack* attSprite;
    AttackComp* att;
    Entity* enemy;
    MovementComp::MOVE_TYPE isFacing;
    if (isPlayer) {
        att = player->getAtkComp();
        attSprite = player->getAttackSprite();
        enemy = opponent;
        isFacing = player->getMoveComp()->isFacing();
    } else {
        att = opponent->getAtkComp();
        attSprite = att->getAttackEntity();
        enemy = player;
        isFacing = opponent->getMoveComp()->isFacing();
    } 
    switch (isFacing) {
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
    onAttackCollision(player);
}

void CollisionSystem::onAttackCollision(Entity* attacker) {
    AttackComp* attack;

    if (attacker->getName() == "Player") {
        attack = dynamic_cast<Drillku*>(attacker)->getAtkComp();
        dynamic_cast<Drillku*>(attacker)->toggleIsAttacking(false);
    } else if (attacker->getName() == "Geygar") {
        attack = dynamic_cast<Enemy*>(attacker)->getAtkComp();
        dynamic_cast<Enemy*>(attacker)->setIsAttacking(false);
        attack->setUNExtendBool(true);
    }

    attack->setExtendBool(false);
    attack->setCanExtend(false);
}
