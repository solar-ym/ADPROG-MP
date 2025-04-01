#pragma once

#include "Factories/Factories.h"

class EnemyPool {
    public:
        EnemyPool(int maxPoolSize, EnemyFactory::ENEMY_TYPE poolType);
        ~EnemyPool();
        Entity* requestObject(int x, int y);
        void returnObject(Enemy* enemy);
    private:
        vector<Entity*> objectPool;
        int maxPoolSize;
        EnemyFactory* factory;
        EnemyFactory::ENEMY_TYPE poolType;
};

