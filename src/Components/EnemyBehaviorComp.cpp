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
    if (enemy == nullptr) enemy = dynamic_cast<Enemy*>(owner);
    // cout << "[Enemy Behavior] Performing" << endl;
    if (this->manager == nullptr) this->manager = manager;
    
    neutral();
}

void EnemyBehaviorComp :: neutral() {
    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    // if (isFacing == MovementComp::RIGHT && status[y][x+1] != 0) {
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

void EnemyBehaviorComp :: detectTarget() {
    int xDif = target->getTileX() - enemy->getTileX();
    int yDif = target->getTileY() - enemy->getTileY();
}

void EnemyBehaviorComp :: chase() {
    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    int xDif = target->getTileX() - x;
    int yDif = target->getTileY() - y;
    
    if(abs(xDif) > abs(yDif) && abs(xDif) <= 4){
        if(xDif>0) {
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
        } 
        else if (abs(yDif) <= 4) {
            if (isFacing == MovementComp::LEFT && manager->hasTunnel(x-1, y)) {
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
        }
    }else{
        if(yDif>0) {
            if (isFacing == MovementComp::DOWN && manager->hasTunnel(x, y+1)) {
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
        }
        else {
            if (isFacing == MovementComp::UP && manager->hasTunnel(x, y-1)) {
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
        }
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
        move->setMovementType(available[randomize(0, available.size()-1)]);
    else {
        cout << "[ERROR : decide facing] Failed to find available tile to move to." << endl;
    }
}

int EnemyBehaviorComp :: randomize(int lowerBound, int upperBound) {
    time_t nTime;
    srand((unsigned) time(&nTime));

    int nRandomizedValue = rand() % (upperBound - lowerBound + 1) + lowerBound;

    return nRandomizedValue;
}