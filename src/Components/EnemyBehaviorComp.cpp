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


    move->setMovingBool(true);

    if (isFacing == MovementComp::RIGHT && status[y][x+1] != 0) {
        move->setMovementType(MovementComp::RIGHT);
        if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::RIGHT);
    } else if (isFacing == MovementComp::RIGHT && status[y][x+1] == 0) {
        decideFacing();
    }
    
    else if (isFacing == MovementComp::LEFT && status[y][x-1] != 0) {
        move->setMovementType(MovementComp::LEFT);
        if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
            move->reCenter(MovementComp::LEFT);
    } else if (isFacing == MovementComp::LEFT && status[y][x-1] == 0) {
        decideFacing();
    }

    else if (isFacing == MovementComp::UP && status[y-1][x] != 0) {
        move->setMovementType(MovementComp::UP);
        if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::UP);
    } else if (isFacing == MovementComp::UP && status[y-1][x] == 0) {
        decideFacing();
    }

    else if (isFacing == MovementComp::DOWN && status[y+1][x] != 0) {
        move->setMovementType(MovementComp::DOWN);
        if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
            move->reCenter(MovementComp::DOWN);
    } else if (isFacing == MovementComp::DOWN && status[y+1][x] == 0) {
        decideFacing();
    } 
    
    else {
        cout << "[ERROR] Failed to find available tile to move to." << endl;
        move->setMovingBool(false);
    }
}

void EnemyBehaviorComp :: decideFacing(){
    MovementComp* move = enemy->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = move->isFacing();
    int x = enemy->getTileX();
    int y = enemy->getTileY();
                    // U, D, L, R
    int available[4] = {0, 0, 0, 0};
    bool foundType = false;

    if (status[y-1][x] != 0) { //UP
        available[0] = 1;
        if (isFacing == MovementComp::DOWN) {
            foundType = true;
            move->setMovementType(MovementComp::UP);
        }
    }
    if (status[y+1][x] != 0) { // DOWN
        available[1] = 1;
        if (isFacing == MovementComp::UP) {
            foundType = true;
            move->setMovementType(MovementComp::DOWN);
        }
    }
    if (status[y][x-1] != 0) { // LEFT
        available[2] = 1;
        if (isFacing == MovementComp::RIGHT) {
            foundType = true;
            move->setMovementType(MovementComp::LEFT);
        }
    }
    if (status[y][x+1] != 0) { // RIGHT
        available[3] = 1;
        if (isFacing == MovementComp::LEFT) {
            foundType = true;
            move->setMovementType(MovementComp::RIGHT);
        }
    }

    if (!foundType) {
        for (int i; i < 4; i++) {
            if (available[i] == 1) {
                cout << "Found tile: " << i << endl;
                switch (i) {
                    case 0:
                    move->setMovementType(MovementComp::UP);
                    break;
                    case 1:
                    move->setMovementType(MovementComp::DOWN);
                    break;
                    case 2:
                    move->setMovementType(MovementComp::LEFT);
                    break;
                    case 3:
                    move->setMovementType(MovementComp::RIGHT);
                    break;
                }
                break;
            }
        }
    }

}

int EnemyBehaviorComp :: randomize(int lowerBound, int upperBound) {
    time_t nTime;
    srand((unsigned) time(&nTime));

    int nRandomizedValue = rand() % (upperBound - lowerBound + 1) + lowerBound;

    return nRandomizedValue;
}