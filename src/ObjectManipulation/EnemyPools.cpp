#include "EnemyPools.h"

EnemyPool :: EnemyPool(int maxPoolSize, EnemyFactory::ENEMY_TYPE poolType){
    this->maxPoolSize = maxPoolSize;
    this->poolType = poolType;

    while (objectPool.size() < maxPoolSize) {
        if (poolType = factory->POOKIE)
            objectPool.push_back(factory->create(factory->POOKIE, -999, -999));
        else if (poolType = factory->GEYGAR)
            objectPool.push_back(factory->create(factory->GEYGAR, -999, -999));
        // objectPool.back(). [ make enemy not move here ]
    }
}

EnemyPool :: ~EnemyPool(){
    for(Entity* en: objectPool)
        if(en!=nullptr)
            delete en;
}

Entity* EnemyPool :: requestObject(int x, int y) { // take objeect from pool
    for(int i=0; i<objectPool.size(); i++){
        Entity* enemy = objectPool[i];
        // grabs the first obj in the pool thats still there and returns it
        if(enemy != nullptr) {
            enemy->setTileXY(x, y);
            objectPool[i] = nullptr;
            return enemy;
        }
    }
    cout << "[ERROR] EnemyPool :: requestObject() Failed to acquire enemy." << endl;
    return nullptr;
}
        
void EnemyPool :: returnObject(Enemy* enemy) { //put obj back in pool
    for(int i=0; i<objectPool.size(); i++)
        if(objectPool[i]==nullptr) {
            objectPool[i] = enemy;
            return;
        }
}
