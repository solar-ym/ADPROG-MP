#include "EnemyBehaviorComp.h"

EnemyBehaviorComp :: EnemyBehaviorComp() 
    : Component("BehaviorComp") {}

void EnemyBehaviorComp :: attachComponent(Entity* owner) {
    Component::attachComponent(owner);
}

void EnemyBehaviorComp :: makeTarget(Drillku* player) {
    if (target == nullptr) target = player;
}

void EnemyBehaviorComp :: perform(TunnelManager* manager) {
    if (internalTime < 200) internalTime++;
    if (enemy == nullptr) enemy = dynamic_cast<Enemy*>(owner);
    if (this->manager == nullptr) this->manager = manager;
    
    // if (targetDetected() || enemy->getGhostMode()) {
        chase();
    // }
    // else
        // neutral();
}

void EnemyBehaviorComp :: neutral() {
    enemy->setGhostMode(false);

    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    if (isFacing == MovementComp::RIGHT && manager->hasTunnel(x+1, y)) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::RIGHT);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::RIGHT);
    } else if (isFacing == MovementComp::RIGHT && !(manager->hasTunnel(x+1, y))) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::RIGHT);
        prevFacing = move->isFacing();
        decideFacing();
    }
    
    else if (isFacing == MovementComp::LEFT && manager->hasTunnel(x-1, y)) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::LEFT);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::LEFT);
    } else if (isFacing == MovementComp::LEFT && !(manager->hasTunnel(x-1, y))) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::LEFT);
        prevFacing = move->isFacing();
        decideFacing();
    }

    else if (isFacing == MovementComp::UP && manager->hasTunnel(x, y-1)) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::UP);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::UP);
    } else if (isFacing == MovementComp::UP && !(manager->hasTunnel(x, y-1))) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::UP);
        prevFacing = move->isFacing();
        decideFacing();
    }

    else if (isFacing == MovementComp::DOWN && manager->hasTunnel(x, y+1)) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::DOWN);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::DOWN);
    } else if (isFacing == MovementComp::DOWN && !(manager->hasTunnel(x, y+1))) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::DOWN);
        prevFacing = move->isFacing();
        decideFacing();
    } 
    
    else {
        cout << "[ERROR : neutral] Failed to find available tile to move to." << endl;
        move->setMovingBool(false);
    }

    move->setMovingBool(true);
}

bool EnemyBehaviorComp :: targetDetected() {
    int xDif = target->getTileX() - enemy->getTileX();
    int yDif = target->getTileY() - enemy->getTileY();

    if ( abs(xDif) <= 2 && abs(yDif) <= 2 )  
        return true;
    else
        return false;
}

void EnemyBehaviorComp :: chase() {
    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    int xDif = target->getTileX() - x;
    int yDif = target->getTileY() - y;
    
    if(abs(xDif) > abs(yDif)){
        if(xDif>0) {
            if (manager->hasTunnel(x+1, y) && !(enemy->getGhostMode())) {
                if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
                    move->reCenter(MovementComp::RIGHT);
                prevFacing = move->isFacing();
                move->setMovementType(MovementComp::RIGHT);
            } else if (enemy->getGhostMode()) {
                ghostChase();
            } else if (!(manager->hasTunnel(x+1, y)) && internalTime >= 70) {
                enemy->setGhostMode(true);
                internalTime = 0;
            } else {
                if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
                    move->reCenter(MovementComp::RIGHT);
                prevFacing = move->isFacing();
                decideFacing();
            }
        } 
        else {
            if (manager->hasTunnel(x-1, y) && !(enemy->getGhostMode())) {
                if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
                    move->reCenter(MovementComp::LEFT);
                prevFacing = move->isFacing();
                move->setMovementType(MovementComp::LEFT);
            } else if (enemy->getGhostMode()) {
                ghostChase();
            } else if (!(manager->hasTunnel(x-1, y))&& internalTime >= 70) {
                enemy->setGhostMode(true);
                internalTime = 0;
            } else {
                if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
                    move->reCenter(MovementComp::LEFT);
                prevFacing = move->isFacing();
                decideFacing();
            }
        }
    }else {
        if(yDif>0) {
            if (manager->hasTunnel(x, y+1) && !(enemy->getGhostMode())) {
                if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
                    move->reCenter(MovementComp::DOWN);
                prevFacing = move->isFacing();
                move->setMovementType(MovementComp::DOWN);
            } else if (enemy->getGhostMode()) {
                ghostChase();
            } else if (!(manager->hasTunnel(x, y+1))&& internalTime >= 70) {
                enemy->setGhostMode(true);
                internalTime = 0;
            } else {
                if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
                    move->reCenter(MovementComp::DOWN);
                prevFacing = move->isFacing();
                decideFacing();
            }
        }
        else {
            if (manager->hasTunnel(x, y-1) && !(enemy->getGhostMode())) {
                if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
                    move->reCenter(MovementComp::UP);
                prevFacing = move->isFacing();
                move->setMovementType(MovementComp::UP);
            } else if (enemy->getGhostMode()) {
                ghostChase();
            } else if (!(manager->hasTunnel(x, y-1))&& internalTime >= 70) {
                enemy->setGhostMode(true);
                internalTime = 0;
            }
            
            else {
                if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
                    move->reCenter(MovementComp::UP);
                prevFacing = move->isFacing();
                decideFacing();
            }
        }
    }

    move->setMovingBool(true);
}

void EnemyBehaviorComp :: ghostChase() {
    MovementComp* move = enemy->getMoveComp();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    move->moveFreely(target->getSprite()->getPosition());

    if ((manager->hasTunnel(x, y)) && internalTime >= 70){
        move->reCenter(MovementComp::RIGHT);
        enemy->setGhostMode(false);
        internalTime = 0;
    }
}

void EnemyBehaviorComp :: decideFacing(){
    MovementComp* move = enemy->getMoveComp();
    int x = enemy->getTileX();
    int y = enemy->getTileY();
    vector<MovementComp::MOVE_TYPE> available;
    
    if (manager->hasTunnel(x, y-1)) { //UP
        available.push_back(MovementComp::UP);
    }
    if (manager->hasTunnel(x, y+1)) { // DOWN
        available.push_back(MovementComp::DOWN);
    }
    if (manager->hasTunnel(x-1, y)) { // LEFT
        available.push_back(MovementComp::LEFT);
    }
    if (manager->hasTunnel(x+1, y)) { // RIGHT
        available.push_back(MovementComp::RIGHT);
    }
    
    if (available.size() != 0)
        move->setMovementType(available[MovementComp::randomize(0, available.size()-1)]);
    else {
        cout << "[ERROR : decide facing] Failed to find available tile to move to." << endl;
    }
}

// void EnemyBehaviorComp :: findTunnel() {

// }