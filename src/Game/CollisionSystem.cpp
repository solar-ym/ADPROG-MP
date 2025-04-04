#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {}

/*
    Handles the checking of all collisions that can occur in the game.
*/
void CollisionSystem::listen(Scene* scene, vector<Enemy*> enemies, Drillku* player, TunnelManager* manager) {
    BattleScene* battle = dynamic_cast<BattleScene*>(scene);
    vector<Rock*> rocks = battle->getAllRocks();
    Veggie* veggie = battle->getRoundVeggie();
    
    // Timed to player death
    if (internalTime > 80) {
        scene->reloadRoundData();
        internalTime = 0;
        running = false;
    }
    
    // Collisions for all enemies
    for (int i = 0; i < enemies.size(); i++) {
        // Sees if the player hits a rock
        for (Rock* r : rocks) {
            if(r->getTileX() == enemies[i]->getTileX() &&
               r->getTileY() == enemies[i]->getTileY())
               enemies[i]->squash();
        }
        
        // Sees if the enemy collides with the player or player attack
        if(enemies[i]->getTileX() == player->getTileX() &&
            enemies[i]->getTileY() == player->getTileY() &&
            !(enemies[i]->getIsSquashed()) && !(enemies[i]->getIsDead()) && !(enemies[i]->getIsDying()))
            onPlayerCollision(1, player);
        if(forcefulComputation(player, enemies[i], true) && player->getAtkComp()->isVisible()) {
            enemyCollided = true;
            onAttackCollision(scene, player, enemies[i]);
        }
        else {
            enemyCollided = false;
            enemies[i]->setIsDying(false);
        }

        // Checks if the player has collided with a Geygar's attack
        if (enemies[i]->getAtkComp() != nullptr && forcefulComputation(player, enemies[i], false) 
            && enemies[i]->getAtkComp()->isVisible()) {
            onPlayerCollision(1, player);
            onAttackCollision(enemies[i]);
        } 
        
        // Checks if a Geygar's attack collides with a wall 
        if (enemies[i]->getAtkComp() != nullptr && collisionComputation(enemies[i], manager) &&
            enemies[i]->getAtkComp()->isVisible())
            onAttackCollision(enemies[i]);
    }

    // Player collisions

    // Sees if player collides with a rock
    for (Rock* r : rocks) {
        if(r->getTileX() == player->getTileX() &&
           r->getTileY() == player->getTileY())
            onPlayerCollision(0, player);
    }

    //  Sees if player attack collides with a wall
    if (collisionComputation(player, manager) && player->getHairVisibility() && !enemyCollided)
        onAttackCollision(player);

    // Sees if the player has gotten the veggie
    if(veggie->getTileX() == player->getTileX() &&
        veggie->getTileY() == player->getTileY() && veggie->getEnabled() &&
            cooldown > 80) {
            veggie->setTileXY(999,999);
            veggie->setEnabled(false);
            player->setLives(Drillku::INCREASELIVES);
            cooldown = 0;
        }
    update();
}

// Called when the player should be killed
void CollisionSystem::onPlayerCollision(int deathType, Drillku* player) {
    if (internalTime == 0) {
        player->kill(deathType);
        running = true;
    }
}

// Called to check if an attack collides with a wall / non-tunnel tile
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

/*
    Called to check attack collisions.
    Named such for its brute force methods.... (could not get other collision methods to work
    because of EntityAttack's quirkiness.)

    Just checks if something is on any of the tiles that the EntityAttack occupies.
*/
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
    cooldown++;
}

// For killing enemies
void CollisionSystem::onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy){
    if (enemy->getIsDead()) {
        enemy->setTileXY(999,999);
    } else {
        enemy->kill();
    }
    onAttackCollision(player);
}

// For EntityAttack behavior after hitting a wall
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
