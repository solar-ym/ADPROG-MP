#pragma once

#include "../Objects/Entity.h"
#include "../Objects/Enemies/Enemy.h"
#include "../ObjectManipulation/Factories.h"

class EnemyPool {
    public:
        EnemyPool(int maxPoolSize, EnemyFactory::enemyType poolType);
        ~EnemyPool();
        Entity* requestObject();
        void returnObject(Enemy* enemy);
    private:
        vector<Entity*> objectPool;
        int maxPoolSize;
        EnemyFactory* factory;
        EnemyFactory::enemyType poolType;
};

