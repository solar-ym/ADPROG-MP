#include "EnemyBehaviorComp.h"

EnemyBehaviorComp :: EnemyBehaviorComp() 
    : Component("BehaviorComp") {}

void EnemyBehaviorComp :: attachComponent(Entity* owner) {
    Component::attachComponent(owner);
}

void EnemyBehaviorComp :: perform(int status[][DIRT_WIDTH]) {
    if (enemy == nullptr) enemy = dynamic_cast<Enemy*>(owner);

    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            this->status[i][j] = status[i][j];
        }
    }
    // cout << "[Enemy Behavior] Performing" << endl;
    neutral();
}

void EnemyBehaviorComp :: neutral() {
    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();

    if (isFacing == MovementComp::RIGHT && status[y][x+1] != 0) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::RIGHT);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::RIGHT);
    } else if (isFacing == MovementComp::RIGHT && status[y][x+1] == 0) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::RIGHT);
        prevFacing = move->isFacing();
        decideFacing();
    }
    
    else if (isFacing == MovementComp::LEFT && status[y][x-1] != 0) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::LEFT);
        move->setMovementType(MovementComp::LEFT);
    } else if (isFacing == MovementComp::LEFT && status[y][x-1] == 0) {
        if (prevFacing == MovementComp::UP || prevFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::LEFT);
        prevFacing = move->isFacing();
        decideFacing();
    }

    else if (isFacing == MovementComp::UP && status[y-1][x] != 0) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::UP);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::UP);
    } else if (isFacing == MovementComp::UP && status[y-1][x] == 0) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::UP);
        prevFacing = move->isFacing();
        decideFacing();
    }

    else if (isFacing == MovementComp::DOWN && status[y+1][x] != 0) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::DOWN);
        prevFacing = move->isFacing();
        move->setMovementType(MovementComp::DOWN);
    } else if (isFacing == MovementComp::DOWN && status[y+1][x] == 0) {
        if (prevFacing == MovementComp::LEFT || prevFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::DOWN);
        prevFacing = move->isFacing();
        decideFacing();
    } 
    
    else {
        cout << "[ERROR] Failed to find available tile to move to." << endl;
        move->setMovingBool(false);
    }

    cout << "PrevFacing: " << prevFacing << endl;
    move->setMovingBool(true);
}

void EnemyBehaviorComp :: decideFacing(){
    MovementComp* move = enemy->getMoveComp();
    int x = enemy->getTileX();
    int y = enemy->getTileY();
    vector<MovementComp::MOVE_TYPE> available;

    if (status[y-1][x] != 0) { //UP
        available.push_back(MovementComp::UP);
    }
    if (status[y+1][x] != 0) { // DOWN
        available.push_back(MovementComp::DOWN);
    }
    if (status[y][x-1] != 0) { // LEFT
        available.push_back(MovementComp::LEFT);
    }
    if (status[y][x+1] != 0) { // RIGHT
        available.push_back(MovementComp::RIGHT);
    }

    move->setMovementType(available[randomize(0, available.size()-1)]);
}

int EnemyBehaviorComp :: randomize(int lowerBound, int upperBound) {
    time_t nTime;
    srand((unsigned) time(&nTime));

    int nRandomizedValue = rand() % (upperBound - lowerBound + 1) + lowerBound;

    return nRandomizedValue;
}