#pragma once

#include "../Objects/Entity.h"

class EnemyPool {
	public:
        EnemyPool(int maxPoolSize);
	    ~EnemyPool();
	    Entity* requestObject();
	    void releaseObject(Entity* enemy);
    private:
        vector<Entity*> objectPool;
        int maxPoolSize;
};