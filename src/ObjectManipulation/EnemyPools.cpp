#include "EnemyPools.h"

EnemyPool::EnemyPool(int maxPoolSize){
    this->maxPoolSize = maxPoolSize;
}

EnemyPool::~EnemyPool(){
    for(Entity* bl: objectPool)
        if(bl!=nullptr)
            delete bl;
}

Entity* EnemyPool::requestObject() { // take objeect from pool
    for(int i=0; i<objectPool.size(); i++){
        Entity* bl = objectPool[i];
        if(bl!=nullptr){
            std::cout << " Aquire: " << bl->getName() << std::endl;
            objectPool[i] = nullptr;
            return bl;
        }
    }
    if(objectPool.size()<maxPoolSize){
        objectPool.push_back(nullptr);
        Entity* bl = new Entity(
            "bullet"+std::to_string(objectPool.size()),
            "shot1",tileSize);
        std::cout << " Aquire: " << bl->getName() << std::endl;
        return bl;
    }
    std::cout << " Cannot create bullet"<< std::endl;
    return nullptr;
}
        
void EnemyPool::releaseObject(Entity* bullet) { //put obj back in pool
    for(int i=0; i<objectPool.size(); i++)
        if(objectPool[i]==nullptr){
            std::cout << "Release: " << bullet->getName() << std::endl;
            objectPool[i] = bullet;
            bullet->setTileXY(-1,-1);
            return;
        }
}
